#include <cassert>
#include <cstdlib>
#include <filesystem>
#include <sstream>
#include <iostream>

#include "apps/admin/AdminApp.h"
#include "finance/Repo.h"

namespace fs = std::filesystem;

void test_list_transactions() {
    setenv("PERSIST_BASE_DIR", "admin_list_data", 1);
    fs::remove_all("admin_list_data");

    finance::FinanceRepo repo;
    repo.load();
    finance::Lancamento l;
    l.id = repo.nextId();
    l.tipo = finance::Tipo::Outros;
    l.subtipo.clear();
    l.descricao = "A";
    l.valor = 1.0;
    l.moeda = "BRL";
    l.data = l.id.substr(4,10);
    l.entrada = true;
    l.projeto_id.clear();
    l.conta.clear();
    repo.add(l);
    l.id = repo.nextId();
    l.descricao = "B";
    repo.add(l);
    repo.save();

    AdminApp app;
    const char* argv[] = {"admin", "fin-list"};
    std::ostringstream oss;
    auto* old = std::cout.rdbuf(oss.rdbuf());
    app.run(2, const_cast<char**>(argv));
    std::cout.rdbuf(old);
    std::string out = oss.str();
    assert(out.find("A") != std::string::npos);
    assert(out.find("B") != std::string::npos);
}

