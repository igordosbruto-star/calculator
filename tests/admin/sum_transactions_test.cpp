#include <cassert>
#include <cstdlib>
#include <filesystem>
#include <sstream>
#include <iostream>

#include "apps/admin/AdminApp.h"
#include "finance/Repo.h"

namespace fs = std::filesystem;

void test_sum_transactions() {
    setenv("PERSIST_BASE_DIR", "admin_sum_data", 1);
    fs::remove_all("admin_sum_data");

    finance::FinanceRepo repo;
    repo.load();
    finance::Lancamento l;
    l.id = repo.nextId();
    l.tipo = finance::Tipo::Outros;
    l.subtipo.clear();
    l.descricao = "E1";
    l.valor = 100.0;
    l.moeda = "BRL";
    l.data = l.id.substr(4,10);
    l.entrada = true;
    l.projeto_id.clear();
    l.conta.clear();
    repo.add(l);
    l.id = repo.nextId();
    l.descricao = "S1";
    l.valor = 40.0;
    l.entrada = false;
    repo.add(l);
    repo.save();

    double before = repo.sum(finance::Filtro{});
    assert(before != 0.0);
    AdminApp app;
    const char* argv1[] = {"admin", "fin-sum"};
    app.run(2, const_cast<char**>(argv1));
    double after = repo.sum(finance::Filtro{});
    assert(before == after);

    finance::Filtro f;
    f.entrada = true;
    double entradas = repo.sum(f);
    const char* argv2[] = {"admin", "fin-sum", "entrada"};
    app.run(3, const_cast<char**>(argv2));
    assert(entradas == repo.sum(f));
}

