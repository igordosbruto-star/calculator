#include <finance/Repo.h>
#include <core/paths.h>
#include <core/atomic_write.h>
#include <cassert>
#include <fstream>
#include <filesystem>

using namespace finance;

void test_repo_load_invalid_json() {
    const std::string rel = "finance/invalid.json";
    const std::string path = ::Persist::dataPath(rel);
    ::Persist::atomicWrite(std::filesystem::path(path), "{ invalid");
    FinanceRepo repo;
    assert(!repo.load(rel));
}

void test_repo_save_invalid_json_preserves_existing() {
    const std::string rel = "finance/preserve.json";
    const std::string path = ::Persist::dataPath(rel);
    std::filesystem::remove(path);

    FinanceRepo good;
    Lancamento a{"1", Tipo::Compra, "", "", 1.0, "BRL", "2025-01-01", true, "", "", {}};
    assert(good.add(a));
    assert(good.save(rel));

    std::ifstream f(path);
    std::string orig((std::istreambuf_iterator<char>(f)), {});

    FinanceRepo bad;
    Lancamento b{std::string("\xff",1), Tipo::Compra, "", "", 1.0, "BRL", "2025-01-01", true, "", "", {}};
    assert(bad.add(b));
    assert(!bad.save(rel));

    std::ifstream f2(path);
    std::string after((std::istreambuf_iterator<char>(f2)), {});
    assert(after == orig);
}

