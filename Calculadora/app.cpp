// ==========================================
// Arquivo: app.cpp
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
#include <chrono>
#include <ctime>
#include <chrono>

// Bibliotecas Personalizadas
#include "Debug.h"
#include "persist.h"   // JSON + CSV (MaterialDTO, save/load, Settings)
#include "modulos.h"   // Material, Corte, App, Como

// ------------------------------------------------------------
// Helpers apenas visíveis neste arquivo
// ------------------------------------------------------------
namespace {

    // Compara por R$/m² e retorna maior/menor
    Como compararPorM2(const Material& a, const Material& b) {
        Como r;
        const double v1 = a.capPorm2();
        const double v2 = b.capPorm2();

        if (v1 > v2) {
            r.maior = {a.capNome(), v1};
            r.menor = {b.capNome(), v2};
            wr::p("COMPARA", "Maior", "Green");
        } else if (v1 < v2) {
            r.maior = {b.capNome(), v2};
            r.menor = {a.capNome(), v1};
            wr::p("COMPARA", "Menor", "Green");
        } else {
            r.maior = {a.capNome(), v1};
            r.menor = {b.capNome(), v2};
            wr::p("COMPARA", "Iguais", "Green");
        }
        return r;
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
    q = compararPorM2(mats[0], mats[1]);
    wr::p("TESTE", "Final do teste...", "Yellow");

    return true;
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
    cortes.clear();

    char resp = 's';
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    while (resp == 's' || resp == 'S') {
        std::string nome;
        double largura = 0.0, comprimento = 0.0;

        std::cout << "\nNome do corte | ";
        std::getline(std::cin, nome);

        std::cout << "Largura (m) | ";
        if (!(std::cin >> largura)) largura = 0.0;

        std::cout << "Comprimento (m) | ";
        if (!(std::cin >> comprimento)) comprimento = 0.0;

        cortes.emplace_back(nome, largura, comprimento, preco);
        cortes.back().imprimir();

        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cout << "Adicionar outro corte? (s/n) | ";
        if (!(std::cin >> resp)) resp = 'n';
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }
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
    escolherPreco();
    solicitarCortes();

    std::cout << "\nExportar cortes para CSV? (s/n) | ";
    char resp = 'n';
    if (!(std::cin >> resp)) resp = 'n';
    if (resp == 's' || resp == 'S') {
        auto now = std::chrono::system_clock::now();
        std::time_t t = std::chrono::system_clock::to_time_t(now);
        std::tm tm = *std::localtime(&t);
        std::ostringstream fname;
        fname << "cortes_" << std::put_time(&tm, "%Y-%m-%d") << ".csv";
        if (Persist::saveCutsCSV(fname.str(), cortes)) {
            wr::p("CSV", fname.str() + " exportado com sucesso.", "Green");
        } else {
            wr::p("CSV", "Falha ao exportar " + fname.str(), "Red");
        }
    }

    exportar();

    std::cout << "\n";
    wr::p("APP", "Finalizando..", "Green");
}
