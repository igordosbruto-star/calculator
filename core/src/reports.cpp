#include "core/reports.h"

#include <filesystem>
#include <fstream>
#include <iomanip>
#include <sstream>

namespace fs = std::filesystem;

namespace core {
namespace reports {

static std::string twoDigits(int v) {
    std::ostringstream oss;
    oss << std::setw(2) << std::setfill('0') << v;
    return oss.str();
}

static std::string fourDigits(int v) {
    std::ostringstream oss;
    oss << std::setw(4) << std::setfill('0') << v;
    return oss.str();
}

Summary monthlySummary(const finance::FinanceRepo& repo, int year, int month) {
    Summary s;
    std::string ano = fourDigits(year);
    std::string mes = twoDigits(month);
    finance::Filtro f;
    f.dt_ini = ano + "-" + mes + "-01";
    f.dt_fim = ano + "-" + mes + "-31";
    for (const auto& l : repo.query(f)) {
        if (l.entrada) s.entradas += l.valor;
        else s.saidas += l.valor;
    }
    return s;
}

std::pair<std::string, std::string> generateMonthlyReport(const finance::FinanceRepo& repo, int year, int month) {
    Summary s = monthlySummary(repo, year, month);
    std::string ano = fourDigits(year);
    std::string mes = twoDigits(month);
    std::string base = "out/reports/" + ano + "-" + mes;
    fs::create_directories(fs::path(base).parent_path());

    std::string csvPath = base + ".csv";
    std::ofstream csv(csvPath);
    csv << "Entradas,Saidas\n";
    csv << std::fixed << std::setprecision(2) << s.entradas << ',' << s.saidas << "\n";

    std::string pdfPath = base + ".pdf";
    std::ofstream pdf(pdfPath);
    pdf << "Relatorio " << ano << '-' << mes << "\n";
    pdf << "Entradas: " << std::fixed << std::setprecision(2) << s.entradas << "\n";
    pdf << "Saidas: " << std::fixed << std::setprecision(2) << s.saidas << "\n";

    return {csvPath, pdfPath};
}

} // namespace reports
} // namespace core

