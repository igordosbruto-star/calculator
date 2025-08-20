#include "SalesApp.h"
#include <iostream>

#include "ApplicationCore.h" // Provided by the existing DUKE project

SalesApp::SalesApp() : core_(new duke::ApplicationCore()) {
    // Load materials and customers on startup
    core_->carregarJSON();
}

SalesApp::~SalesApp() {
    delete core_;
}

int SalesApp::run(int argc, char** argv) {
    if (argc < 2) {
        showHelp();
        return 0;
    }
    std::string command = argv[1];
    std::vector<std::string> args(argv + 2, argv + argc);

    if (command == "new-order") {
        handleNewOrder(args);
    } else if (command == "list-customers") {
        handleListCustomers();
    } else if (command == "inventory") {
        handleInventory();
    } else {
        std::cerr << "Unknown command: " << command << "\n";
        showHelp();
    }
    return 0;
}

void SalesApp::showHelp() const {
    std::cout << "DUKE Sales App Commands:\n";
    std::cout << "  new-order <args>     Create a new sales order\n";
    std::cout << "  list-customers       List all registered customers\n";
    std::cout << "  inventory            Show stock of finished products\n";
}

void SalesApp::handleNewOrder(const std::vector<std::string>& args) {
    // Espera: new-order <cliente> <item> <quantidade>
    if (args.size() < 3) {
        std::cerr << "Uso: new-order <cliente> <item> <quantidade>\n";
        return;
    }
    int qtd = std::stoi(args[2]);
    if (core_->criarPedido(args[0], args[1], qtd)) {
        std::cout << "Pedido criado com sucesso.\n";
    } else {
        std::cerr << "Falha ao criar pedido.\n";
    }
}

void SalesApp::handleListCustomers() const {
    auto clientes = core_->listarClientes();
    for (const auto& c : clientes) {
        std::cout << "- " << c.nome << "\n";
    }
}

void SalesApp::handleInventory() const {
    auto estoque = core_->listarEstoque();
    for (const auto& m : estoque) {
        std::cout << "- " << m.nome << " (R$" << m.valor << ")\n";
    }
}

