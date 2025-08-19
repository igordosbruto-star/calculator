#include <finance/Report.h>
#include <cassert>
#include <fstream>
#include <sstream>
#include <filesystem>

using namespace finance;
namespace fs = std::filesystem;

void test_report_mes() {
    fs::remove_all("out");

    FinanceRepo repo;
    repo.add({"1", Tipo::Compra, "sub", "desc1", 100.0, "BRL", "2025-08-05", false, "", "caixa", {}});
    repo.add({"2", Tipo::Vendas, "sub2", "desc2", 50.0, "BRL", "2025-08-10", true, "", "banco", {}});
    repo.add({"3", Tipo::Compra, "sub", "desc3", 30.0, "BRL", "2025-07-01", false, "", "caixa", {}});

    std::ostringstream oss;
    std::string path = reportMes(repo, 2025, 8, oss);
    std::string out = oss.str();
    assert(out.find("2025-08-05") != std::string::npos);
    assert(out.find("-100.00") != std::string::npos);
    assert(out.find("+50.00") != std::string::npos);

    std::ifstream csv(path);
    assert(csv.is_open());
    std::string content((std::istreambuf_iterator<char>(csv)), {});
    assert(content.find("2025-08-05") != std::string::npos);
    assert(content.find("-100.00") != std::string::npos);
    assert(content.find("+50.00") != std::string::npos);
}

