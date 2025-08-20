#include "ProductionApp.h"
#include <iostream>
#include <algorithm>
#include "ApplicationCore.h"

ProductionApp::ProductionApp() : core_(new duke::ApplicationCore()) {
    // Carrega dados básicos (stubbed na versão de testes)
    core_->carregarJSON();

    // Define um modelo de produção com BOM e uma variante
    using namespace production;
    ModeloProducao cadeira("CHAIR", "Cadeira Luxo");

    Componente estrutura;
    estrutura.nome = "Estrutura";
    estrutura.materiais.push_back({"Madeira", "unidade", 2});
    estrutura.materiais.push_back({"Prego", "unidade", 4});

    Componente revestimento;
    revestimento.nome = "Revestimento";
    revestimento.materiais.push_back({"Tecido", "m", 3});

    cadeira.adicionarComponente(estrutura);
    cadeira.adicionarComponente(revestimento);
    cadeira.definirVariavel("tecido", "Veludo Rose Gold");

    modelos_.push_back(cadeira);

    // Cria duas ordens para demonstrar o fluxo
    orders_.push_back({"A1", &modelos_.back()});
    orders_.push_back({"A2", &modelos_.back()});

    // Estoque inicial de matérias‑primas
    estoque_["Madeira"] = 3;   // suficiente apenas para uma ordem
    estoque_["Prego"] = 10;
    estoque_["Tecido"] = 6;
}

ProductionApp::~ProductionApp() {
    delete core_;
}

int ProductionApp::run(int argc, char** argv) {
    if (argc < 2) {
        showHelp();
        return 0;
    }
    std::string command = argv[1];
    std::vector<std::string> args(argv + 2, argv + argc);
    if (command == "list-orders") {
        handleListOrders();
    } else if (command == "start-order") {
        handleStartOrder(args);
    } else if (command == "finish-order") {
        handleFinishOrder(args);
    } else {
        std::cerr << "Unknown command: " << command << "\n";
        showHelp();
    }
    return 0;
}

void ProductionApp::showHelp() const {
    std::cout << "DUKE Production App Commands:\n";
    std::cout << "  list-orders          List active production orders\n";
    std::cout << "  start-order <id>     Start work on an order\n";
    std::cout << "  finish-order <id>    Mark an order as complete\n";
}

void ProductionApp::handleListOrders() const {
    std::cout << "Listing production orders...\n";
    for (const auto& o : orders_) {
        if (o.finished) continue; // apenas ordens ativas
        std::cout << o.id << " - ";
        if (o.modelo) {
            const std::string& tecido = o.modelo->variavel("tecido");
            if (!tecido.empty()) {
                std::cout << tecido << " - ";
            }
        }
        std::cout << (o.started ? "in progress" : "pending") << "\n";
    }
}

void ProductionApp::handleStartOrder(const std::vector<std::string>& args) {
    if (args.empty()) {
        std::cerr << "Usage: start-order <id>\n";
        return;
    }
    const std::string& id = args[0];
    auto it = std::find_if(orders_.begin(), orders_.end(), [&](const ProductionOrder& o){ return o.id == id; });
    if (it == orders_.end()) {
        std::cerr << "Order not found\n";
        return;
    }
    ProductionOrder& ord = *it;
    if (ord.started) {
        std::cerr << "Order already started\n";
        return;
    }
    // Verifica estoque
    for (const auto& comp : ord.modelo->componentes()) {
        for (const auto& mat : comp.materiais) {
            double disp = estoque_[mat.nome];
            if (disp < mat.quantidade) {
                std::cout << "Insufficient material: " << mat.nome << "\n";
                return;
            }
        }
    }
    // Consome materiais
    for (const auto& comp : ord.modelo->componentes()) {
        for (const auto& mat : comp.materiais) {
            estoque_[mat.nome] -= mat.quantidade;
        }
    }
    ord.started = true;
    std::cout << "Order " << ord.id << " started\n";
}

void ProductionApp::handleFinishOrder(const std::vector<std::string>& args) {
    if (args.empty()) {
        std::cerr << "Usage: finish-order <id>\n";
        return;
    }
    const std::string& id = args[0];
    auto it = std::find_if(orders_.begin(), orders_.end(), [&](const ProductionOrder& o){ return o.id == id; });
    if (it == orders_.end()) {
        std::cerr << "Order not found\n";
        return;
    }
    ProductionOrder& ord = *it;
    if (!ord.started) {
        std::cerr << "Order not started\n";
        return;
    }
    if (ord.finished) {
        std::cerr << "Order already finished\n";
        return;
    }
    ord.finished = true;
    std::cout << "Order " << ord.id << " finished\n";
}

