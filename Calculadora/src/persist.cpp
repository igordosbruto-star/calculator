#include "persist.hpp"
#include "core/persist.h" // para atomicWrite e utilidades

#include <chrono>
#include <ctime>
#include <iomanip>
#include <sstream>
#include <cctype>
#include <filesystem>
#include <algorithm>
#include <fstream>
#include <system_error>

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
    std::error_code ec;
    bool created = fs::create_directories(dir, ec);
    if (ec) {
        wr::p("PERSIST", dir.string() + " create fail: " + ec.message(), "Red");
    } else if (created) {
        wr::p("PERSIST", dir.string() + " criado.", "Green");
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

// Lê o JSON indicado e preenche `out` com os dados do plano
bool loadPlanoJSON(const std::string& file, PlanoCorteDTO& out) {
    const fs::path p = file;
    try {
        std::ifstream f(p);
        if (!f) {
            wr::p("PERSIST", p.string() + " open fail", "Red");
            return false;
        }
        json j; f >> j;
        out = j.get<PlanoCorteDTO>();
        return true;
    } catch (const std::exception& e) {
        wr::p("PERSIST", p.string() + " exception: " + e.what(), "Red");
        return false;
    } catch (...) {
        wr::p("PERSIST", p.string() + " unknown exception", "Red");
        return false;
    }
}

bool updateIndex(const PlanoCorteDTO& plano) {
    const fs::path indexPath = fs::path("out") / "planos" / "index.json";
    try {
        if (!indexPath.parent_path().empty()) {
            std::error_code ec;
            bool created = fs::create_directories(indexPath.parent_path(), ec);
            if (ec) {
                wr::p("PERSIST", indexPath.parent_path().string() + " create fail: " + ec.message(), "Red");
            } else if (created) {
                wr::p("PERSIST", indexPath.parent_path().string() + " criado.", "Green");
            }
        }

        json j;
        if (fs::exists(indexPath)) {
            std::ifstream f(indexPath);
            if (f) {
                try {
                    f >> j;
                } catch (...) {
                    j = json{};
                }
            }
        }
        if (!j.is_object()) j = json::object();
        if (!j.contains("planos") || !j["planos"].is_array())
            j["planos"] = json::array();

        json entry = {
            {"id", plano.id},
            {"total_valor", plano.total_valor},
            {"total_area_m2", plano.total_area_m2},
            {"porm2", plano.porm2_usado}
        };

        bool replaced = false;
        for (auto& item : j["planos"]) {
            if (item.is_object() && item.value("id", std::string{}) == plano.id) {
                item = entry;
                replaced = true;
                break;
            }
        }
        if (!replaced)
            j["planos"].push_back(entry);

        return atomicWrite(indexPath, j.dump(2));
    } catch (const std::exception& e) {
        wr::p("PERSIST", indexPath.string() + " exception: " + e.what(), "Red");
        return false;
    } catch (...) {
        wr::p("PERSIST", indexPath.string() + " unknown exception", "Red");
        return false;
    }
}

bool loadIndex(std::vector<PlanoIndexEntry>& out) {
    const fs::path indexPath = fs::path("out") / "planos" / "index.json";
    try {
        std::ifstream f(indexPath);
        if (!f) return false;
        json j; f >> j;
        if (!j.is_object() || !j.contains("planos") || !j["planos"].is_array())
            return false;
        out.clear();
        for (const auto& item : j["planos"]) {
            PlanoIndexEntry e;
            e.id = item.value("id", std::string{});
            e.total_valor = item.value("total_valor", 0.0);
            e.total_area_m2 = item.value("total_area_m2", 0.0);
            e.porm2 = item.value("porm2", 0.0);
            out.push_back(e);
        }
        return true;
    } catch (const std::exception& e) {
        wr::p("PERSIST", indexPath.string() + " exception: " + e.what(), "Red");
        return false;
    } catch (...) {
        wr::p("PERSIST", indexPath.string() + " unknown exception", "Red");
        return false;
    }
}

} // namespace Persist

