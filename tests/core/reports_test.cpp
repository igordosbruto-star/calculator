#include <cassert>
#include <filesystem>
#include "core/reports.h"
#include "finance/Repo.h"

namespace fs = std::filesystem;

void test_monthly_summary() {
    finance::FinanceRepo repo;
    repo.add({"1", finance::Tipo::Compra, "sub", "out", 30.0, "BRL", "2025-07-01", false, "", "caixa", {}});
    repo.add({"2", finance::Tipo::Vendas, "sub", "in", 100.0, "BRL", "2025-08-05", true, "", "caixa", {}});
    repo.add({"3", finance::Tipo::Compra, "sub", "out2", 50.0, "BRL", "2025-08-10", false, "", "banco", {}});
    auto sum = core::reports::monthlySummary(repo, 2025, 8);
    assert(sum.entradas == 100.0);
    assert(sum.saidas == 50.0);
}

void test_generate_report() {
    fs::remove_all("out");
    finance::FinanceRepo repo;
    repo.add({"1", finance::Tipo::Vendas, "s", "in", 25.0, "BRL", "2025-08-01", true, "", "", {}});
    auto paths = core::reports::generateMonthlyReport(repo, 2025, 8);
    assert(fs::exists(paths.first));
    assert(fs::exists(paths.second));
}

