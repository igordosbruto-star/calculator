#include "AdminApp.h"
#include <iostream>
#include <sstream>
#include "finance/Repo.h"
#include "finance/SupplierRepo.h"

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
    if (args.size() < 2) {
        std::cerr << "Uso: fin-add <descricao> <valor> [entrada|saida]\n";
        return;
    }
    finance::Lancamento l;
    l.id = repo_->nextId();
    l.tipo = finance::Tipo::Outros;
    l.subtipo.clear();
    l.descricao = args[0];
    std::stringstream ss(args[1]);
    ss >> l.valor;
    if (!ss || l.valor <= 0.0) {
        std::cerr << "Valor invalido\n";
        return;
    }
    l.moeda = "BRL";
    l.data = l.id.substr(4, 10);
    l.entrada = true;
    if (args.size() >= 3) {
        if (args[2] == "saida") l.entrada = false;
    }
    l.projeto_id.clear();
    l.conta.clear();
    l.tags.clear();
    if (!repo_->add(l)) {
        std::cerr << "Falha ao adicionar lancamento\n";
        return;
    }
    if (!repo_->save()) {
        std::cerr << "Falha ao salvar\n";
        return;
    }
    std::cout << "Adicionado " << l.id << "\n";
}

void AdminApp::handleListTransactions() const {
    auto vec = repo_->query(finance::Filtro{});
    for (const auto& l : vec) {
        std::cout << l.id << " " << l.descricao << " "
                  << (l.entrada ? "+" : "-") << l.valor << "\n";
    }
}

void AdminApp::handleSumTransactions(const std::vector<std::string>& args) const {
    finance::Filtro f;
    if (!args.empty()) {
        if (args[0] == "entrada") f.entrada = true;
        else if (args[0] == "saida") f.entrada = false;
    }
    double total = repo_->sum(f);
    std::cout << "Total: " << total << "\n";
}

void AdminApp::handleSuppliers() const {
    finance::SupplierRepo srepo;
    if (!srepo.load()) {
        std::cout << "Nenhum fornecedor cadastrado\n";
        return;
    }
    for (const auto& s : srepo.all()) {
        std::cout << s.id << " " << s.nome << "\n";
    }
}

