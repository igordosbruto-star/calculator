#include "AdminApp.h"
#include <iostream>
#include "finance/Repo.h"

AdminApp::AdminApp() : repo_(new finance::FinanceRepo()) {
    repo_->load();
}

AdminApp::~AdminApp() {
    delete repo_;
}

int AdminApp::run(int argc, char** argv) {
    if (argc < 2) {
        showHelp();
        return 0;
    }
    std::string command = argv[1];
    std::vector<std::string> args(argv + 2, argv + argc);
    if (command == "fin-add") {
        handleAddTransaction(args);
    } else if (command == "fin-list") {
        handleListTransactions();
    } else if (command == "fin-sum") {
        handleSumTransactions(args);
    } else if (command == "suppliers") {
        handleSuppliers();
    } else {
        std::cerr << "Unknown command: " << command << "\n";
        showHelp();
    }
    return 0;
}

void AdminApp::showHelp() const {
    std::cout << "DUKE Admin App Commands:\n";
    std::cout << "  fin-add <args>        Add a new financial transaction\n";
    std::cout << "  fin-list              List all financial transactions\n";
    std::cout << "  fin-sum <filters>     Sum transactions by criteria\n";
    std::cout << "  suppliers             Manage supplier catalogue\n";
}

void AdminApp::handleAddTransaction(const std::vector<std::string>& args) {
    std::cout << "Adding transaction...\n";
    // TODO: parse arguments and call repo_->add(...)
}

void AdminApp::handleListTransactions() const {
    std::cout << "Listing transactions...\n";
    // TODO: iterate over repo_ entries
}

void AdminApp::handleSumTransactions(const std::vector<std::string>& args) const {
    std::cout << "Summing transactions...\n";
    // TODO: call repo_->sum(...) with filters
}

void AdminApp::handleSuppliers() const {
    std::cout << "Managing suppliers...\n";
    // TODO: implement supplier management
}

