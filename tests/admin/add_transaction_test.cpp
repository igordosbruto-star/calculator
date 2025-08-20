#include <cassert>
#include <cstdlib>
#include <filesystem>
#include <sstream>
#include <iostream>

#include "apps/admin/AdminApp.h"
#include "finance/Repo.h"

namespace fs = std::filesystem;

void test_add_transaction() {
    setenv("PERSIST_BASE_DIR", "admin_add_data", 1);
    fs::remove_all("admin_add_data");

    AdminApp app;
    const char* argv[] = {"admin", "fin-add", "Teste", "5.5"};
    std::ostringstream oss;
    auto* old = std::cout.rdbuf(oss.rdbuf());
    app.run(4, const_cast<char**>(argv));
    std::cout.rdbuf(old);

    finance::FinanceRepo repo;
    bool ok = repo.load();
    assert(ok);
    auto items = repo.query(finance::Filtro{});
    assert(items.size() == 1);
    assert(items[0].descricao == "Teste");
    assert(items[0].valor == 5.5);
}

