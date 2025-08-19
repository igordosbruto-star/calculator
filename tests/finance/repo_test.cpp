#include <finance/Repo.h>
#include <cassert>

using namespace finance;

void test_repo_sum() {
    FinanceRepo repo;
    Lancamento a{"1", Tipo::Compra, "sub", "", 10.0, "BRL", "2025-01-01", true, "", "", {}};
    Lancamento b{"2", Tipo::Compra, "sub", "", 5.0, "BRL", "2025-01-02", false, "", "", {}};
    assert(repo.add(a));
    assert(repo.add(b));
    Filtro f;
    double total = repo.sum(f);
    assert(total == 5.0);
    f.dt_ini = "2025-01-02";
    total = repo.sum(f);
    assert(total == -5.0);
}

void test_repo_validacao() {
    FinanceRepo repo;
    Lancamento inval{"1", Tipo::Compra, "sub", "", -2.0, "BRL", "2025-01-01", true, "", "", {}};
    Lancamento invalData{"2", Tipo::Compra, "sub", "", 5.0, "BRL", "2025-13-01", true, "", "", {}};
    assert(!repo.add(inval));
    assert(!repo.add(invalData));
    assert(repo.query({}).empty());
}
