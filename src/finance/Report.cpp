#include "finance/Report.h"
#include "finance/Serialize.h"

#include <filesystem>
#include <fstream>
#include <iomanip>
#include <sstream>

namespace fs = std::filesystem;

namespace finance {

// Função auxiliar para formatar números com zeros à esquerda
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

std::string reportMes(const FinanceRepo& repo, int ano, int mes, std::ostream& out) {
    std::string anoStr = fourDigits(ano);
    std::string mesStr = twoDigits(mes);

    Filtro f;
    f.dt_ini = anoStr + "-" + mesStr + "-01";
    f.dt_fim = anoStr + "-" + mesStr + "-31";

    auto itens = repo.query(f);

    out << "Data | Tipo | Subtipo | Descrição | ±Valor | Conta\n";
    for (const auto& l : itens) {
        out << l.data << " | "
            << to_string(l.tipo) << " | "
            << l.subtipo << " | "
            << l.descricao << " | "
            << (l.entrada ? "+" : "-") << std::fixed << std::setprecision(2) << l.valor << " | "
            << l.conta << "\n";
    }

    std::string csvPath = "out/finance/" + anoStr + "-" + mesStr + "-report.csv";
    fs::create_directories(fs::path(csvPath).parent_path());
    std::ofstream csv(csvPath);
    csv << "Data,Tipo,Subtipo,Descricao,Valor,Conta\n";
    for (const auto& l : itens) {
        csv << l.data << ','
            << to_string(l.tipo) << ','
            << l.subtipo << ','
            << l.descricao << ','
            << (l.entrada ? "+" : "-") << std::fixed << std::setprecision(2) << l.valor << ','
            << l.conta << '\n';
    }

    return csvPath;
}

} // namespace finance

