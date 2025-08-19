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
#include "cli/parser.h"
#include "cli/utils.h"
#include "cli/commands.h"
#include "finance/Serialize.h"
namespace duke {
// ------------------------------------------------------------
// Implementação do App
// ------------------------------------------------------------

void App::importarCSV() {
    std::cout << "Importar materiais do CSV para JSON? (s/n) | ";
    char imp = 'n';
    if (!(std::cin >> imp)) imp = 'n';
    // Descarta o restante da linha para evitar interferência em próximas leituras
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    if (imp == 's' || imp == 'S') {
        std::vector<MaterialDTO> tmp;
        if (::Persist::loadCSV("materiais.csv", tmp) && !tmp.empty()) {
            if (::Persist::saveJSON("materiais.json", tmp, 1)) {
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
    return core.carregarJSON(base, mats);
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
            case 1: {
                auto itens = core.listarMateriais(base);
                std::cout << "\nMateriais cadastrados:\n";
                if (itens.empty()) {
                    std::cout << "(vazio)\n";
                } else {
                    for (size_t i = 0; i < itens.size(); ++i) {
                        const auto& m = itens[i];
                        std::cout << i + 1 << ") " << m.nome << " [" << m.tipo << "]"
                                  << " | " << UN_MONE << m.valor
                                  << " | " << m.largura << " x " << m.comprimento << UN_AREA
                                  << "\n";
                    }
                }
                break;
            }
            case 2: cli::adicionarMaterial(base, mats); break;
            case 3: cli::editarMaterial(base, mats); break;
            case 4: cli::removerMaterial(base, mats); break;
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
    if (!::Persist::validar(m)) {
        wr::p("APP", "Material invalido, nada salvo.", "Red");
        return;
    }
    base.push_back(m);
    cli::salvarReconstruir(base, mats);
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
    auto itens = core.listarMateriais(base);
    std::cout << "\nMateriais cadastrados:\n";
    if (itens.empty()) {
        std::cout << "(vazio)\n";
        return;
    }
    for (size_t i = 0; i < itens.size(); ++i) {
        const auto& m = itens[i];
        std::cout << i + 1 << ") " << m.nome << " [" << m.tipo << "]"
                  << " | " << UN_MONE << m.valor
                  << " | " << m.largura << " x " << m.comprimento << UN_AREA
                  << "\n";
    }
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
    auto res = core.compararMateriais(mats, ids);
    std::cout << "ID | Nome | porm2\n";
    for (size_t i = 0; i < ids.size(); ++i) {
        const auto& r = res[i];
        std::string extra;
        if (r.menor) extra = " <menor>";
        if (r.maior) extra = " <maior>";
        std::cout << ids[i] + 1 << " | " << r.nome << " | "
                  << UN_MONE << r.porm2 << extra << "\n";
    }
}

// ---------- Financeiro ----------

void App::finAdicionar() {
    finRepo.load();
    finance::Lancamento l;
    l.id = finRepo.nextId();
    std::string tipo = ui::readString("Tipo: ");
    if (!tipo.empty()) l.tipo = finance::tipo_from_string(tipo);
    l.subtipo = ui::readString("Subtipo: ");
    l.descricao = ui::readString("Descricao: ");
    l.valor = ui::readDouble("Valor: ");
    l.data = ui::readString("Data (AAAA-MM-DD): ");
    std::string es = ui::readString("Entrada(E) ou Saida(S): ");
    l.entrada = !(es == "S" || es == "s");
    l.moeda = "BRL";
    if (finRepo.add(l)) {
        finRepo.save();
        wr::p("FIN", "Lancamento adicionado.", "Green");
    } else {
        wr::p("FIN", "Dados invalidos (valor >0 e data AAAA-MM-DD)", "Red");
    }
}

void App::finListar() {
    finRepo.load();
    auto itens = finRepo.query({});
    for (const auto& l : itens) {
        std::cout << l.id << " | " << finance::to_string(l.tipo)
                  << " | " << l.subtipo << " | "
                  << (l.entrada?"+":"-") << l.valor
                  << " | " << l.data << " | " << l.descricao << "\n";
    }
}

void App::finSomar() {
    finRepo.load();
    finance::Filtro f;
    std::string ini = ui::readString("Data inicial (opcional): ");
    if (!ini.empty()) f.dt_ini = ini;
    std::string fim = ui::readString("Data final (opcional): ");
    if (!fim.empty()) f.dt_fim = fim;
    double total = finRepo.sum(f);
    std::cout << "Total: " << total << "\n";
}

void App::escolherPreco() {
    int opcao = 1;
    if      (settings.prefer == "cheapest") opcao = 1;
    else if (settings.prefer == "priciest") opcao = 2;
    else {
        opcao = cli::lerOpcao12(1);
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
        totalArea += c.getArea();
        totalValor += c.getValor();

        // Constrói o DTO correspondente
        CorteDTO dto{nome, largura, comprimento, preco, c.getArea(), c.getValor(), false};
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
    // Verifica se salvamento em JSON foi bem-sucedido
    if (!Persist::savePlanoJSON(dir, plano)) {
        wr::p("PERSIST", "Falha ao salvar plano em JSON. Operacao abortada.", "Red");
        return;
    }
    // Garante exportacao para CSV
    if (!Persist::savePlanoCSV(dir, plano)) {
        wr::p("PERSIST", "Falha ao salvar plano em CSV. Operacao abortada.", "Red");
        return;
    }
    // Atualiza indice global; aborta se falhar
    if (!Persist::updateIndex(plano)) {
        wr::p("PERSIST", "Falha ao atualizar indice de planos. Operacao abortada.", "Red");
        return;
    }

    // Exibe ao usuário onde foi salvo
    wr::p("PERSIST", "Plano salvo em: " + dir, "Green");
}

void App::exportar() {
    std::cout << "\nExportar base para CSV? (s/n) | ";
    char resp = 'n';
    if (!(std::cin >> resp)) resp = 'n';
    // Descarta o restante da linha para evitar interferência em próximas leituras
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    if (resp == 's' || resp == 'S') {
        if (::Persist::saveCSV("materiais.csv", base)) {
            wr::p("CSV", "materiais.csv exportado com sucesso.", "Green");
        } else {
            wr::p("CSV", "Falha ao exportar materiais.csv", "Red");
        }
    }
}

void App::iniciar(bool autoMode) {
    wr::p("APP", "Iniciando..", "Green");
    std::cout << "\n";

    settings = ::Persist::loadOrCreateSettings();
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
                int opt = ui::promptMenuKey({"Criar", "Listar", "Comparar", "Financeiro", "Config", "Sair"},
                                            {'C','L','M','F','O','S'});
                switch (opt) {
                    case 0: state = ui::MenuState::Criar; break;
                    case 1: state = ui::MenuState::Listar; break;
                    case 2: state = ui::MenuState::Comparar; break;
                    case 3: state = ui::MenuState::Financeiro; break;
                    case 4: state = ui::MenuState::Config; break;
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
                    cli::listarMateriais(base);
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
            case ui::MenuState::Financeiro: {
                ui::renderBreadcrumb({ui::toString(ui::MenuState::Principal), "Financeiro"});
                int opt = ui::promptMenuKey({"Adicionar", "Listar", "Soma", "Voltar"}, {'A','L','S','V'});
                if (opt == 0) {
                    finAdicionar();
                } else if (opt == 1) {
                    finListar();
                } else if (opt == 2) {
                    finSomar();
                }
                ui::readString("Pressione ENTER para voltar...", std::cin, std::cout);
                state = ui::MenuState::Principal;
                break;
            }
            case ui::MenuState::Sair:
                break;
        }
    }

    std::cout << "\n";
    wr::p("APP", "Finalizando..", "Green");
}
} // namespace duke
