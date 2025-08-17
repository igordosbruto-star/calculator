#include "persist.hpp"
#include "persist.h" // para atomicWrite e utilidades

#include <chrono>
#include <ctime>
#include <iomanip>
#include <sstream>
#include <cctype>
#include <filesystem>
#include <algorithm>

namespace fs = std::filesystem;

namespace Persist {

std::string nowIso8601() {
    const auto now = std::chrono::system_clock::now();
    const std::time_t t = std::chrono::system_clock::to_time_t(now);
    std::tm tm{}; 
#ifdef _WIN32
    localtime_s(&tm, &t);
#else
    localtime_r(&t, &tm);
#endif
    std::ostringstream oss;
    oss << std::put_time(&tm, "%Y-%m-%dT%H:%M:%S");
    return oss.str();
}

static std::string sanitize(const std::string& s) {
    std::string out; out.reserve(s.size());
    for (unsigned char ch : s) {
        if (std::isalnum(ch)) out.push_back(static_cast<char>(std::tolower(ch)));
        else if (ch == ' ') out.push_back('_');
        else out.push_back('_');
    }
    return out;
}

std::string makeId(const std::string& projeto) {
    std::string iso = nowIso8601();
    for (auto& ch : iso) {
        if (ch == 'T') ch = '_';
    }
    iso.erase(std::remove(iso.begin(), iso.end(), ':'), iso.end());
    return iso + "_" + sanitize(projeto);
}

std::string outPlanosDirFor(const std::string& projeto, const std::string& id) {
    (void)projeto; // id já contém o nome do projeto
    const fs::path dir = fs::path("out") / "planos" / id;
    try {
        fs::create_directories(dir);
    } catch (...) {
        // falha silenciosa: retorno mesmo assim
    }
    return dir.string();
}

bool savePlanoJSON(const std::string& dir, const PlanoCorteDTO& plano) {
    const fs::path p = fs::path(dir) / "plano.json";
    try {
        json j = plano;
        return atomicWrite(p, j.dump(2));
    } catch (const std::exception& e) {
        wr::p("PERSIST", p.string() + " exception: " + e.what(), "Red");
        return false;
    } catch (...) {
        wr::p("PERSIST", p.string() + " unknown exception", "Red");
        return false;
    }
}

bool savePlanoCSV(const std::string& dir, const PlanoCorteDTO& plano) {
    const fs::path p = fs::path(dir) / "plano.csv";
    try {
        std::ostringstream oss;
        oss << "nome;largura_m;comprimento_m;porm2;area_m2;valor;rot90\n";
        for (const auto& c : plano.cortes) {
            std::string safe = c.nome;
            for (auto& ch : safe) if (ch == ';') ch = ',';
            oss << safe << ';'
                << to_str_br(c.largura_m) << ';'
                << to_str_br(c.comprimento_m) << ';'
                << to_str_br(c.porm2) << ';'
                << to_str_br(c.area_m2) << ';'
                << to_str_br(c.valor) << ';'
                << (c.rot90 ? "1" : "0") << '\n';
        }
        return atomicWrite(p, oss.str());
    } catch (const std::exception& e) {
        wr::p("PERSIST", p.string() + " exception: " + e.what(), "Red");
        return false;
    } catch (...) {
        wr::p("PERSIST", p.string() + " unknown exception", "Red");
        return false;
    }
}

} // namespace Persist

