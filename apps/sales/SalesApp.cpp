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
    // TODO: Implement order creation by interacting with ApplicationCore
    std::cout << "Creating a new order...\n";
}

void SalesApp::handleListCustomers() const {
    // TODO: Retrieve and display customers from ApplicationCore
    std::cout << "Listing customers...\n";
}

void SalesApp::handleInventory() const {
    // TODO: Show stock of finished products
    std::cout << "Showing inventory...\n";
}

