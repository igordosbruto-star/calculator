#include <finance/Repo.h>
#include <cassert>

using namespace finance;

void test_repo_sum() {
    FinanceRepo repo;
    Lancamento a{"1", Tipo::Compra, "sub", "", 10.0, "BRL", "2025-01-01", true, "", "", {}};
    Lancamento b{"2", Tipo::Compra, "sub", "", 5.0, "BRL", "2025-01-02", false, "", "", {}};
    repo.add(a);
    repo.add(b);
    Filtro f;
    double total = repo.sum(f);
    assert(total == 5.0);
    f.dt_ini = "2025-01-02";
    total = repo.sum(f);
    assert(total == -5.0);
}
