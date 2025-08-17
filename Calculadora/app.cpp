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

// Bibliotecas Personalizadas
#include "Debug.h"
#include "Persist.h"   // JSON + CSV (MaterialDTO, save/load, Settings)
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
            std::cout << "Maior\n";
        } else if (v1 < v2) {
            r.maior = {b.capNome(), v2};
            r.menor = {a.capNome(), v1};
            std::cout << "Menor\n";
        } else {
            r.maior = {a.capNome(), v1};
            r.menor = {b.capNome(), v2};
            std::cout << "Iguais\n";
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
            std::cout << "Entrada invalida. Usando opcao " << padrao << ".\n";
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
void App::iniciar() {
    wr::p("APP", "Iniciando..", "Green");
    std::cout << "\n";

    // ===========================
    // 0) Carregar settings
    // ===========================
    Persist::Settings settings = Persist::loadOrCreateSettings(); // data/settings.json

    // Configuração de casas decimais (limitamos 0..6 por segurança)
    dec = std::clamp(settings.decimal_places, 0, 6);
    std::cout << std::fixed << std::setprecision(dec);

    // ===========================
    // 1) Opcional: importar CSV -> JSON
    // ===========================
    {
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

    // ===========================
    // 2) Carregar JSON (fonte de verdade) ou criar defaults
    // ===========================
    std::vector<MaterialDTO> base;
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
        wr::p("DATA", "materiais.json carregado (versao " + std::to_string(version) + ")", "Green");
    }

    // ===========================
    // 3) Reconstruir objetos Material
    // ===========================
    auto mats = reconstruirMateriais(base);

    if (mats.size() < 2) {
        wr::p("ERRO", "Precisam existir pelo menos 2 materiais para comparar.", "Red");
        return;
    }

    // ===========================
    // 4) Comparar por R$/m² (exemplo entre os dois primeiros)
    // ===========================
    wr::p("TESTE", "Inicio do teste...", "Yellow");
    q = compararPorM2(mats[0], mats[1]);
    wr::p("TESTE", "Final do teste...", "Yellow");

    // ===========================
    // 5) Escolha do mais barato/caro — respeitando settings.prefer
    // ===========================
    int opcao = 1;
    if      (settings.prefer == "cheapest") opcao = 1;
    else if (settings.prefer == "priciest") opcao = 2;
    else {
        // "ask": pergunta ao usuário como antes
        opcao = lerOpcao12(1);
    }

    if (opcao == 1) {
        std::cout << "Vamos calcular com o mais barato! (" << q.menor.nome << ")\n";
        preco = q.menor.valor;
    } else {
        std::cout << "Vamos calcular com o mais caro! (" << q.maior.nome << ")\n";
        preco = q.maior.valor;
    }

    // ===========================
    // 6) Calculo do corte (exemplo)
    // ===========================
    Corte corte("Tabua de 56,5cm", 0.20, 0.565, preco);
    corte.imprimir();

    // ===========================
    // 7) Exportar CSV (opcional)
    // ===========================
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

    std::cout << "\n";
    wr::p("APP", "Finalizando..", "Green");
}
