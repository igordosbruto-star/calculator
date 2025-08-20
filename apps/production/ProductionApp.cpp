#include "ProductionApp.h"
#include <iostream>
#include "ApplicationCore.h"

ProductionApp::ProductionApp() : core_(new duke::ApplicationCore()) {
    core_->carregarJSON();
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
    // TODO: Use core_ to load orders
}

void ProductionApp::handleStartOrder(const std::vector<std::string>& args) {
    std::cout << "Starting order...\n";
    // TODO: Start selected order and reserve materials
}

void ProductionApp::handleFinishOrder(const std::vector<std::string>& args) {
    std::cout << "Finishing order...\n";
    // TODO: Mark order as finished and update stock
}

