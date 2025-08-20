#include <cassert>
#include <cstdlib>
#include <filesystem>
#include <sstream>
#include <iostream>

#include "apps/admin/AdminApp.h"
#include "finance/SupplierRepo.h"

namespace fs = std::filesystem;

void test_suppliers() {
    setenv("PERSIST_BASE_DIR", "admin_suppliers_data", 1);
    fs::remove_all("admin_suppliers_data");

    finance::SupplierRepo repo;
    finance::Supplier s1{"F1", "ACME", "contato"};
    finance::Supplier s2{"F2", "Beta", "email"};
    repo.add(s1);
    repo.add(s2);
    repo.save();

    AdminApp app;
    const char* argv[] = {"admin", "suppliers"};
    std::ostringstream oss;
    auto* old = std::cout.rdbuf(oss.rdbuf());
    app.run(2, const_cast<char**>(argv));
    std::cout.rdbuf(old);
    std::string out = oss.str();
    assert(out.find("ACME") != std::string::npos);
    assert(out.find("Beta") != std::string::npos);
}

