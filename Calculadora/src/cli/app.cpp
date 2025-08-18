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
#include "cli/App.h"
#include "core/format.h"
#include "Corte.h"
#include "core/Debug.h"
#include "plano_corte.h"
#include "persist.hpp"
#include "ui/Menu.h"
#include "ui/Screens.h"
#include "core.h"

// ------------------------------------------------------------
// Helpers apenas visíveis neste arquivo
// ------------------------------------------------------------
namespace {

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

    // Exibe materiais cadastrados
    void listarMateriais(const std::vector<MaterialDTO>& base) {
        std::cout << "\nMateriais cadastrados:\n";
        if (base.empty()) {
            std::cout << "(vazio)\n";
            return;
        }
        for (size_t i = 0; i < base.size(); ++i) {
            const auto& m = base[i];
            std::cout << i + 1 << ") " << m.nome << " [" << m.tipo << "]"
                      << " | " << UN_MONE << m.valor
                      << " | " << m.largura << " x " << m.comprimento << UN_AREA
                      << "\n";
        }
    }

    // Reconstrói vetor de Materiais e persiste base
    void salvarReconstruir(std::vector<MaterialDTO>& base, std::vector<Material>& mats) {
        mats = core::reconstruirMateriais(base);
        Persist::saveJSON("materiais.json", base, 1);
    }


    // Adiciona novo material
    void adicionarMaterial(std::vector<MaterialDTO>& base, std::vector<Material>& mats) {
        MaterialDTO m;
        std::cout << "Nome: ";
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::getline(std::cin, m.nome);
        std::cout << "Tipo (unitario/linear/cubico) [linear]: ";
        std::string tipo;
        std::getline(std::cin, tipo);
        if (!tipo.empty()) {
            if (tipo == "unitario" || tipo == "linear" || tipo == "cubico") {
                m.tipo = tipo;
            } else {
                wr::p("APP", "Tipo invalido. Usando 'linear'.", "Yellow");
            }
        }
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
    int schemaVersion = 0;
    if (!Persist::loadJSON("materiais.json", base, &schemaVersion) || base.empty()) {
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
        oss << "materiais.json carregado (versao " << schemaVersion << ")";
        wr::p("DATA", oss.str(), "Green");
    }

    mats = core::reconstruirMateriais(base);

    if (mats.size() < 2) {
        wr::p("ERRO", "Precisam existir pelo menos 2 materiais para comparar.", "Red");
        return false;
    }

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

// Cria material a partir de entradas específicas por tipo
void App::criarMaterial() {
    ui::renderBreadcrumb({ui::toString(ui::MenuState::Principal),
                           ui::toString(ui::MenuState::Criar),
                           "Material"});
    MaterialDTO m;
    m.nome = ui::readString("Nome: ");
    int tipo = ui::readInt("Tipo (1-Unitario 2-Linear 3-Cubico): ");
    switch (tipo) {
        case 1:
            m.tipo = "unitario";
            m.valor = ui::readDouble("Preco por unidade: ");
            break;
        case 3:
            m.tipo = "cubico";
            m.valor = ui::readDouble("Preco por m3: ");
            break;
        default:
            m.tipo = "linear";
            m.valor = ui::readDouble("Preco por metro: ");
            m.comprimento = ui::readDouble("Comprimento padrao (m): ");
            break;
    }
    if (!Persist::validar(m)) {
        wr::p("APP", "Material invalido, nada salvo.", "Red");
        return;
    }
    base.push_back(m);
    salvarReconstruir(base, mats);
    wr::p("APP", "Material criado.", "Green");
}

// Lista cortes cadastrados lendo o índice global
void App::listarCortes() {
    ui::renderBreadcrumb({ui::toString(ui::MenuState::Principal),
                           ui::toString(ui::MenuState::Listar),
                           "Cortes"});
    std::vector<Persist::PlanoIndexEntry> itens;
    if (!Persist::loadIndex(itens) || itens.empty()) {
        std::cout << "(vazio)\n";
        return;
    }
    for (size_t i = 0; i < itens.size(); ++i) {
        const auto& e = itens[i];
        std::cout << i + 1 << ") " << e.id
                  << " | area:" << e.total_area_m2
                  << "m2 | total:" << UN_MONE << e.total_valor
                  << " | porm2:" << UN_MONE << e.porm2
                  << "\n";
    }
}

// Compara materiais selecionados pelo usuário
void App::compararMateriais() {
    ui::renderBreadcrumb({ui::toString(ui::MenuState::Principal),
                           ui::toString(ui::MenuState::Comparar),
                           "Materiais"});
    listarMateriais(base);
    std::string linha = ui::readString("IDs separados por espaco: ");
    std::istringstream iss(linha);
    std::vector<int> ids; int id;
    while (iss >> id) {
        if (id >= 1 && id <= static_cast<int>(mats.size()))
            ids.push_back(id - 1);
    }
    if (ids.size() < 2) {
        std::cout << "Selecione ao menos dois materiais.\n";
        return;
    }
    std::vector<Material> sel;
    for (int i : ids) sel.push_back(mats[static_cast<size_t>(i)]);
    auto [menor, maior] = core::extremosPorM2(sel);
    std::cout << "ID | Nome | porm2\n";
    for (int i : ids) {
        const auto& m = mats[static_cast<size_t>(i)];
        std::string extra;
        if (m.capNome() == menor.nome) extra = " <menor>";
        if (m.capNome() == maior.nome) extra = " <maior>";
        std::cout << i + 1 << " | " << m.capNome() << " | "
                  << UN_MONE << m.capPorm2() << extra << "\n";
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
    std::vector<Corte> cortes;           // mantém objetos de domínio
    std::vector<CorteDTO> cortesDTO;     // paralelamente, DTOs para persistência
    double totalArea = 0.0;              // soma das áreas
    double totalValor = 0.0;             // soma dos valores
    char cont = 's';

    // Nome opcional do projeto para compor o identificador
    std::string projeto;
    std::cout << "\nNome do projeto: ";
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    std::getline(std::cin, projeto);

    while (cont == 's' || cont == 'S') {
        std::string nome;
        double largura = 0.0;
        double comprimento = 0.0;

        std::cout << "\nNome do corte: ";
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
        cortes.push_back(c);
        totalArea += c.capArea();
        totalValor += c.capValor();

        // Constrói o DTO correspondente
        CorteDTO dto{nome, largura, comprimento, preco, c.capArea(), c.capValor(), false};
        cortesDTO.push_back(dto);

        std::cout << "Adicionar outro corte? (s/n) | ";
        std::cin >> cont;
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }

    std::cout << "\nResumo final:";
    for (const auto& c : cortes) {
        c.imprimir();
    }
    std::cout << "\nTotal geral: " << UN_MONE << totalValor << "\n";

    // Monta DTO do plano com totais e preço usado
    PlanoCorteDTO plano;
    plano.projeto = projeto;
    plano.porm2_usado = preco;
    plano.cortes = cortesDTO;
    plano.total_area_m2 = totalArea;
    plano.total_valor = totalValor;
    plano.algoritmo = "manual";
    plano.gerado_em = Persist::nowIso8601();
    plano.id = Persist::makeId(projeto);

    // Persiste o plano em disco
    const std::string dir = Persist::outPlanosDirFor(projeto, plano.id);
    Persist::savePlanoJSON(dir, plano);
    Persist::savePlanoCSV(dir, plano);
    Persist::updateIndex(plano);

    // Exibe ao usuário onde foi salvo
    wr::p("PERSIST", "Plano salvo em: " + dir, "Green");
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

void App::iniciar(bool autoMode) {
    wr::p("APP", "Iniciando..", "Green");
    std::cout << "\n";

    settings = Persist::loadOrCreateSettings();
    if (autoMode) {
        settings.prefer = "cheapest";
        wr::p("APP", "Modo automatico ativado.", "Blue");
    }

    dec = std::clamp(settings.decimal_places, 0, 6);
    std::cout << std::fixed << std::setprecision(dec);

    importarCSV();
    if (!carregarJSON()) return;
    q = core::extremosPorM2(mats);

    ui::MenuState state = ui::MenuState::Principal;
    while (state != ui::MenuState::Sair) {
        switch (state) {
            case ui::MenuState::Principal: {
                ui::clearScreen();
                ui::renderBreadcrumb({ui::toString(ui::MenuState::Principal)});
                int opt = ui::promptMenuKey({"Criar", "Listar", "Comparar", "Config", "Sair"},
                                            {'C','L','M','O','S'});
                switch (opt) {
                    case 0: state = ui::MenuState::Criar; break;
                    case 1: state = ui::MenuState::Listar; break;
                    case 2: state = ui::MenuState::Comparar; break;
                    case 3: state = ui::MenuState::Config; break;
                    default: state = ui::MenuState::Sair; break;
                }
                break;
            }
            case ui::MenuState::Criar: {
                ui::renderBreadcrumb({ui::toString(ui::MenuState::Principal),
                                      ui::toString(ui::MenuState::Criar)});
                int opt = ui::promptMenuKey({"Material", "Corte", "Voltar"}, {'M','C','V'});
                if (opt == 0) {
                    criarMaterial();
                    ui::readString("Pressione ENTER para voltar...", std::cin, std::cout);
                } else if (opt == 1) {
                    escolherPreco();
                    solicitarCortes();
                    exportar();
                    ui::readString("Pressione ENTER para voltar...", std::cin, std::cout);
                }
                state = ui::MenuState::Principal;
                break;
            }
            case ui::MenuState::Listar: {
                ui::renderBreadcrumb({ui::toString(ui::MenuState::Principal),
                                      ui::toString(ui::MenuState::Listar)});
                int opt = ui::promptMenuKey({"Materiais", "Cortes", "Voltar"}, {'M','C','V'});
                if (opt == 0) {
                    listarMateriais(base);
                    ui::readString("Pressione ENTER para voltar...", std::cin, std::cout);
                } else if (opt == 1) {
                    listarCortes();
                    ui::readString("Pressione ENTER para voltar...", std::cin, std::cout);
                }
                state = ui::MenuState::Principal;
                break;
            }
            case ui::MenuState::Comparar: {
                int opt = ui::promptMenuKey({"Materiais", "Voltar"}, {'M','V'});
                if (opt == 0) {
                    compararMateriais();
                    ui::readString("Pressione ENTER para voltar...", std::cin, std::cout);
                }
                state = ui::MenuState::Principal;
                break;
            }
            case ui::MenuState::Config:
                menuMateriais();
                if (mats.size() < 2) {
                    wr::p("ERRO", "Precisam existir pelo menos 2 materiais para comparar.", "Red");
                } else {
                    q = core::extremosPorM2(mats);
                }
                state = ui::MenuState::Principal;
                break;
            case ui::MenuState::Sair:
                break;
        }
    }

    std::cout << "\n";
    wr::p("APP", "Finalizando..", "Green");
}
