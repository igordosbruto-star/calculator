// ==========================================
// Arquivo: App.cpp
// Descrição: Funcionamento do programa (lógica do App)
// ==========================================

// Bibliotecas de Sistema
#include <iostream>
#include <iomanip>
#include <string>
#include <limits>
#include <vector>
#include <algorithm> // std::clamp
#include <sstream>

// Bibliotecas Personalizadas
#include "App.h"
#include "Corte.h"
#include "Debug.h"

// ------------------------------------------------------------
// Helpers apenas visíveis neste arquivo
// ------------------------------------------------------------
namespace {

    Como extremosPorM2(const std::vector<Material>& mats) {
        auto cmp = [](const Material& a, const Material& b){ return a.capPorm2() < b.capPorm2(); };
        auto [min_it, max_it] = std::minmax_element(mats.begin(), mats.end(), cmp);
        return {{min_it->capNome(), min_it->capPorm2()}, {max_it->capNome(), max_it->capPorm2()}};
    }

    // Lê uma opção do usuário garantindo apenas 1 ou 2
    int lerOpcao12(int padrao = 1) {
        int opcao = padrao;
        std::cout << "Quer o calculo com o mais barato ou com o mais caro? (1/2) | ";
        if (!(std::cin >> opcao) || (opcao != 1 && opcao != 2)) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            opcao = padrao;
            wr::p("APP", "Entrada invalida. Usando opcao " + std::to_string(padrao) + ".", "Yellow");
        }
        return opcao;
    }

    // Reconstrói objetos Material a partir dos DTOs carregados do JSON.
    std::vector<Material> reconstruirMateriais(const std::vector<MaterialDTO>& v) {
        std::vector<Material> mats;
        mats.reserve(v.size());
        for (const auto& d : v) {
            mats.emplace_back(d.nome, d.valor, d.largura, d.comprimento);
        }
        return mats;
    }

    // Exibe materiais cadastrados
    void listarMateriais(const std::vector<MaterialDTO>& base) {
        std::cout << "\nMateriais cadastrados:\n";
        if (base.empty()) {
            std::cout << "(vazio)\n";
            return;
        }
        for (size_t i = 0; i < base.size(); ++i) {
            const auto& m = base[i];
            std::cout << i + 1 << ") " << m.nome
                      << " | " << UN_MONE << m.valor
                      << " | " << m.largura << " x " << m.comprimento << UN_AREA
                      << "\n";
        }
    }

    // Reconstrói vetor de Materiais e persiste base
    void salvarReconstruir(std::vector<MaterialDTO>& base, std::vector<Material>& mats) {
        mats = reconstruirMateriais(base);
        Persist::saveJSON("materiais.json", base, 1);
    }

    // Adiciona novo material
    void adicionarMaterial(std::vector<MaterialDTO>& base, std::vector<Material>& mats) {
        MaterialDTO m;
        std::cout << "Nome: ";
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::getline(std::cin, m.nome);
        std::cout << "Valor: ";
        std::cin >> m.valor;
        std::cout << "Largura: ";
        std::cin >> m.largura;
        std::cout << "Comprimento: ";
        std::cin >> m.comprimento;
        base.push_back(m);
        salvarReconstruir(base, mats);
    }

    // Edita material existente
    void editarMaterial(std::vector<MaterialDTO>& base, std::vector<Material>& mats) {
        if (base.empty()) return;
        listarMateriais(base);
        std::cout << "Indice para editar: ";
        size_t idx = 0;
        if (!(std::cin >> idx) || idx < 1 || idx > base.size()) {
            std::cout << "Indice invalido.\n";
            return;
        }
        MaterialDTO& m = base[idx - 1];
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::string nome;
        std::cout << "Nome (" << m.nome << "): ";
        std::getline(std::cin, nome);
        if (!nome.empty()) m.nome = nome;
        std::cout << "Valor (" << m.valor << "): ";
        std::cin >> m.valor;
        std::cout << "Largura (" << m.largura << "): ";
        std::cin >> m.largura;
        std::cout << "Comprimento (" << m.comprimento << "): ";
        std::cin >> m.comprimento;
        salvarReconstruir(base, mats);
    }

    // Remove material por indice
    void removerMaterial(std::vector<MaterialDTO>& base, std::vector<Material>& mats) {
        if (base.empty()) return;
        listarMateriais(base);
        std::cout << "Indice para remover: ";
        size_t idx = 0;
        if (!(std::cin >> idx) || idx < 1 || idx > base.size()) {
            std::cout << "Indice invalido.\n";
            return;
        }
        base.erase(base.begin() + static_cast<long>(idx - 1));
        salvarReconstruir(base, mats);
    }

} // namespace

// ------------------------------------------------------------
// Implementação do App
// ------------------------------------------------------------

void App::importarCSV() {
    std::cout << "Importar materiais do CSV para JSON? (s/n) | ";
    char imp = 'n';
    if (!(std::cin >> imp)) imp = 'n';

    if (imp == 's' || imp == 'S') {
        std::vector<MaterialDTO> tmp;
        if (Persist::loadCSV("materiais.csv", tmp) && !tmp.empty()) {
            if (Persist::saveJSON("materiais.json", tmp, 1)) {
                wr::p("DATA", "Importacao CSV -> JSON concluida (materiais.json atualizado).", "Green");
            } else {
                wr::p("DATA", "Falha ao salvar JSON apos importar CSV.", "Red");
            }
        } else {
            wr::p("DATA", "Falha ao ler materiais.csv ou arquivo vazio.", "Red");
        }
    }
}

bool App::carregarJSON() {
    int version = 0;
    if (!Persist::loadJSON("materiais.json", base, &version) || base.empty()) {
        wr::p("DATA", "Base nao encontrada. Criando materiais padrao...", "Yellow");
        base = {
            {"Pinus 20cm", 17.00, 0.20, 3.00},
            {"MDF 15mm", 180.00, 1.85, 2.75}
        };
        if (Persist::saveJSON("materiais.json", base, 1)) {
            wr::p("DATA", "materiais.json criado.", "Green");
        } else {
            wr::p("DATA", "Falha ao criar materiais.json", "Red");
        }
    } else {
        std::ostringstream oss;
        oss << "materiais.json carregado (versao " << version << ")";
        wr::p("DATA", oss.str(), "Green");
    }

    mats = reconstruirMateriais(base);

    if (mats.size() < 2) {
        wr::p("ERRO", "Precisam existir pelo menos 2 materiais para comparar.", "Red");
        return false;
    }

    wr::p("TESTE", "Inicio do teste...", "Yellow");
    q = extremosPorM2(mats);
    wr::p("COMPARA", "Extremos calculados", "Green");
    wr::p("TESTE", "Final do teste...", "Yellow");

    return true;
}

void App::menuMateriais() {
    while (true) {
        std::cout << "\n--- Materiais ---\n"
                  << "1 - Listar\n"
                  << "2 - Adicionar\n"
                  << "3 - Editar\n"
                  << "4 - Remover\n"
                  << "0 - Continuar\n"
                  << "Opcao: ";
        int op = 0;
        if (!(std::cin >> op)) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            continue;
        }
        switch (op) {
            case 1: listarMateriais(base); break;
            case 2: adicionarMaterial(base, mats); break;
            case 3: editarMaterial(base, mats); break;
            case 4: removerMaterial(base, mats); break;
            case 0: return;
            default:
                std::cout << "Opcao invalida.\n";
                break;
        }
    }
}

void App::escolherPreco() {
    int opcao = 1;
    if      (settings.prefer == "cheapest") opcao = 1;
    else if (settings.prefer == "priciest") opcao = 2;
    else {
        opcao = lerOpcao12(1);
    }

    if (opcao == 1) {
        wr::p("APP", "Vamos calcular com o mais barato! (" + q.menor.nome + ")", "Green");
        preco = q.menor.valor;
    } else {
        wr::p("APP", "Vamos calcular com o mais caro! (" + q.maior.nome + ")", "Green");
        preco = q.maior.valor;
    }
}

void App::solicitarCortes() {
    std::vector<Corte> cortes;
    double total = 0.0;
    char cont = 's';

    while (cont == 's' || cont == 'S') {
        std::string nome;
        double largura = 0.0;
        double comprimento = 0.0;

        std::cout << "\nNome do corte: ";
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::getline(std::cin, nome);
        while (nome.empty()) {
            std::cout << "Nome invalido. Tente novamente.\n";
            std::cout << "Nome do corte: ";
            std::getline(std::cin, nome);
        }
        do {
            std::cout << "Largura (m): ";
            std::cin >> largura;
            if (!(std::cin) || largura <= 0) {
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                std::cout << "Valor invalido. A largura deve ser maior que zero.\n";
            }
        } while (largura <= 0);

        do {
            std::cout << "Comprimento (m): ";
            std::cin >> comprimento;
            if (!(std::cin) || comprimento <= 0) {
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                std::cout << "Valor invalido. O comprimento deve ser maior que zero.\n";
            }
        } while (comprimento <= 0);

        Corte c(nome, largura, comprimento, preco);
        total += c.capValor();
        cortes.push_back(c);

        std::cout << "Adicionar outro corte? (s/n) | ";
        std::cin >> cont;
    }

    std::cout << "\nResumo final:";
    for (const auto& c : cortes) {
        c.imprimir();
    }
    std::cout << "\nTotal geral: " << UN_MONE << total << "\n";
}

void App::exportar() {
    std::cout << "\nExportar base para CSV? (s/n) | ";
    char resp = 'n';
    if (!(std::cin >> resp)) resp = 'n';
    if (resp == 's' || resp == 'S') {
        if (Persist::saveCSV("materiais.csv", base)) {
            wr::p("CSV", "materiais.csv exportado com sucesso.", "Green");
        } else {
            wr::p("CSV", "Falha ao exportar materiais.csv", "Red");
        }
    }
}

void App::iniciar() {
    wr::p("APP", "Iniciando..", "Green");
    std::cout << "\n";

    settings = Persist::loadOrCreateSettings();

    dec = std::clamp(settings.decimal_places, 0, 6);
    std::cout << std::fixed << std::setprecision(dec);

    importarCSV();
    if (!carregarJSON()) return;
    menuMateriais();
    if (mats.size() < 2) {
        wr::p("ERRO", "Precisam existir pelo menos 2 materiais para comparar.", "Red");
        return;
    }
    q = extremosPorM2(mats);
    escolherPreco();
    solicitarCortes();
    exportar();

    std::cout << "\n";
    wr::p("APP", "Finalizando..", "Green");
}
