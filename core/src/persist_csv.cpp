#include "core/persist.h"
#include <sstream>

namespace Persist {

bool saveCSV(const std::string& path, const std::vector<MaterialDTO>& items,
             const std::string& baseDir) {
    for (const auto& m : items) {
        auto err = validar(m);
        if (err.code != duke::ErrorCode::Ok) {
            wr::p("PERSIST", duke::errorMessage(err.code, err.field) + ": " + m.nome, "Red");
            return false;
        }
    }

    std::ostringstream oss;
    oss << "nome;tipo;valor;largura;comprimento\n";

    for (const auto& m : items) {
        std::string safe = m.nome;
        for (auto& ch : safe) if (ch == ';') ch = ',';
        oss << safe << ';'
            << m.tipo << ';'
            << to_str_br(m.valor) << ';'
            << to_str_br(m.largura) << ';'
            << to_str_br(m.comprimento) << "\n";
    }
    return atomicWrite(fs::path(dataPath(path, baseDir)), oss.str());
}

bool loadCSV(const std::string& path, std::vector<MaterialDTO>& out,
             const std::string& baseDir) {
    const std::string p = dataPath(path, baseDir);
    std::ifstream f(p);
    if (!f) {
        wr::p("PERSIST", p + " open fail", "Red");
        return false;
    }

    out.clear();
    std::string line;
    if (!std::getline(f, line)) {
        wr::p("PERSIST", p + " header read fail", "Red");
        return false;
    }

    auto parseNum = [](const std::string& s, double& outVal) -> bool {
        std::string tmp = detail::trim(s);
        for (auto& ch : tmp) if (ch == ',') ch = '.';
        try {
            size_t idx = 0;
            outVal = std::stod(tmp, &idx);
            if (idx != tmp.size()) return false;
            return true;
        } catch (...) {
            return false;
        }
    };

    size_t lineNo = 1;
    int invalidLines = 0;
    while (std::getline(f, line)) {
        ++lineNo;
        if (line.empty()) continue;
        std::vector<std::string> cols;
        cols.reserve(5);
        std::stringstream ss(line);
        std::string item;
        while (std::getline(ss, item, ';')) {
            cols.push_back(item);
        }
        if (cols.size() != 5) {
            wr::p("PERSIST", p + ":" + std::to_string(lineNo) + " coluna invalida", "Yellow");
            ++invalidLines;
            continue;
        }

        MaterialDTO m;
        m.nome = detail::trim(cols[0]);
        m.tipo = detail::trim(cols[1]);
        if (m.tipo.empty()) m.tipo = "linear";
        bool ok = parseNum(cols[2], m.valor) &&
                  parseNum(cols[3], m.largura) &&
                  parseNum(cols[4], m.comprimento);
        auto err = validar(m);
        if (!ok || err.code != duke::ErrorCode::Ok) {
            wr::p("PERSIST", p + ":" + std::to_string(lineNo) + " " + duke::errorMessage(err.code, err.field), "Yellow");
            ++invalidLines;
            continue;
        }
        out.push_back(std::move(m));
    }
    if (out.empty() && invalidLines > 0) return false;
    return true;
}

} // namespace Persist

