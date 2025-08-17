// persist.h
#pragma once

#include <string>
#include <vector>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <algorithm> // find_if, std::clamp
#include <cctype>    // std::isspace
#include <filesystem>
#include <exception>
#include "Debug.h"

namespace fs = std::filesystem;

// ---- DTO de Material (somente dados base) ----
struct MaterialDTO {
    std::string nome;
    double valor = 0.0;
    double largura = 0.0;
    double comprimento = 0.0;
};

// ------------ JSON ------------
#include "third_party/nlohmann/json.hpp"
using nlohmann::json;

inline void to_json(json& j, const MaterialDTO& m) {
    j = json{
        {"nome", m.nome},
        {"valor", m.valor},
        {"largura", m.largura},
        {"comprimento", m.comprimento}
    };
}

inline void from_json(const json& j, MaterialDTO& m) {
    j.at("nome").get_to(m.nome);
    j.at("valor").get_to(m.valor);
    j.at("largura").get_to(m.largura);
    j.at("comprimento").get_to(m.comprimento);
}

// ---- Settings do app ----
struct Settings {
    int         decimal_places = 2;      // casas decimais na saída
    std::string prefer         = "ask";  // "ask" | "cheapest" | "priciest"
};

inline void to_json(json& j, const Settings& s) {
    j = json{
        {"decimal_places", s.decimal_places},
        {"prefer", s.prefer}
    };
}
inline void from_json(const json& j, Settings& s) {
    if (j.contains("decimal_places")) j.at("decimal_places").get_to(s.decimal_places);
    if (j.contains("prefer"))         j.at("prefer").get_to(s.prefer);
}

namespace Persist {

// ----------------------------------------------
// Garante a pasta data/ e devolve "data/<arquivo>"
// ----------------------------------------------
inline std::string dataPath(const std::string& filename) {
    try { fs::create_directory("data"); } catch (...) {}
    return "data/" + filename;
}

// ----------------------------------------------
// Escrita atômica com .tmp e backup .bak
// ----------------------------------------------
inline bool atomicWrite(const fs::path& finalPath, const std::string& content) {
    try {
        if (!finalPath.parent_path().empty())
            fs::create_directories(finalPath.parent_path());

        const fs::path tmpPath = finalPath.string() + ".tmp";
        const fs::path bakPath = finalPath.string() + ".bak";

        // 1) escreve no .tmp
        {
            std::ofstream f(tmpPath, std::ios::out | std::ios::trunc | std::ios::binary);
            if (!f) {
                wr::p("PERSIST", tmpPath.string() + " open fail", "Red");
                return false;
            }
            f.write(content.data(), static_cast<std::streamsize>(content.size()));
            if (!f) {
                wr::p("PERSIST", tmpPath.string() + " write fail", "Red");
                return false;
            }
        }

        // 2) backup do arquivo atual (se existir)
        if (fs::exists(finalPath)) {
            std::error_code ec;
            fs::copy_file(finalPath, bakPath, fs::copy_options::overwrite_existing, ec);
            // falha no backup não é fatal
        }

        // 3) move .tmp -> final
        std::error_code ec2;
        fs::rename(tmpPath, finalPath, ec2);
        if (ec2) {
            // fallback: tenta remover o destino e renomear de novo
            std::error_code ec3;
            fs::remove(finalPath, ec3);
            fs::rename(tmpPath, finalPath, ec2);
            if (ec2) {
                wr::p("PERSIST", finalPath.string() + " rename fail: " + ec2.message(), "Red");
                return false;
            }
        }
        return true;
    } catch (const std::exception& e) {
        wr::p("PERSIST", finalPath.string() + " exception: " + e.what(), "Red");
        return false;
    } catch (...) {
        wr::p("PERSIST", finalPath.string() + " unknown exception", "Red");
        return false;
    }
}

// ----------------------------------------------
// Utilitário: formata double com vírgula decimal
// e ponto fixo (sem depender de locale do SO).
// ----------------------------------------------
inline std::string to_str_br(double x, int precision = 6) {
    std::ostringstream oss;
    oss.setf(std::ios::fixed);
    oss.precision(precision);
    oss << x;
    std::string s = oss.str();
    for (auto& ch : s) if (ch == '.') ch = ',';
    return s;
}

// ----------------- JSON: salvar/carregar -----------------
inline bool saveJSON(const std::string& path, const std::vector<MaterialDTO>& v, int version = 1) {
    json j;
    j["version"]   = version;
    j["materiais"] = v; // usa to_json automaticamente
    return atomicWrite(fs::path(dataPath(path)), j.dump(2));
}

inline bool loadJSON(const std::string& path, std::vector<MaterialDTO>& out, int* out_version = nullptr) {
    const std::string p = dataPath(path);
    std::ifstream f(p);
    if (!f) {
        wr::p("PERSIST", p + " open fail", "Red");
        return false;
    }
    try {
        json j; f >> j;
        if (out_version && j.contains("version")) *out_version = j["version"].get<int>();
        if (j.contains("materiais")) {
            out = j["materiais"].get<std::vector<MaterialDTO>>();
            return true;
        }
        wr::p("PERSIST", p + " missing 'materiais'", "Red");
        return false;
    } catch (const std::exception& e) {
        wr::p("PERSIST", p + " parse error: " + e.what(), "Red");
        return false;
    } catch (...) {
        wr::p("PERSIST", p + " unknown parse error", "Red");
        return false;
    }
}

// -------------------- CSV helpers --------------------
namespace detail {
    inline std::string trim(std::string s) {
        auto not_space = [](unsigned char c){ return !std::isspace(c); };
        s.erase(s.begin(), std::find_if(s.begin(), s.end(), not_space));
        s.erase(std::find_if(s.rbegin(), s.rend(), not_space).base(), s.end());
        return s;
    }
    inline double parse_br_double(std::string s) {
        s = trim(std::move(s));
        // Aceita: "180", "180,00", "1.850,00"
        for (auto& ch : s) {
            if (ch == ',') ch = '.';
        }
        try {
            return std::stod(s);
        } catch (...) {
            return 0.0; // fallback seguro
        }
    }
} // namespace detail

// ------------ CSV (formato BR: ; + vírgula decimal) ------------
inline bool saveCSV(const std::string& path, const std::vector<MaterialDTO>& items) {
    std::ostringstream oss;

    // Cabeçalho
    oss << "nome;valor;largura;comprimento\n";

    for (const auto& m : items) {
        // Sanitize simples para não quebrar CSV com ';'
        std::string safe = m.nome;
        for (auto& ch : safe) if (ch == ';') ch = ',';

        // Números com vírgula decimal (compatível com Planilhas em localidade Brasil)
        oss << safe << ';'
            << to_str_br(m.valor) << ';'
            << to_str_br(m.largura) << ';'
            << to_str_br(m.comprimento) << "\n";
    }
    return atomicWrite(fs::path(dataPath(path)), oss.str());
}

// -------------------- CSV: Leitura --------------------
inline bool loadCSV(const std::string& path, std::vector<MaterialDTO>& out) {
    const std::string p = dataPath(path);
    std::ifstream f(p);
    if (!f) {
        wr::p("PERSIST", p + " open fail", "Red");
        return false;
    }

    out.clear();
    std::string line;

    // Lê primeira linha (cabeçalho). Esperado: nome;valor;largura;comprimento
    if (!std::getline(f, line)) {
        wr::p("PERSIST", p + " header read fail", "Red");
        return false;
    }

    while (std::getline(f, line)) {
        if (line.empty()) continue;

        // Split por ';'
        std::vector<std::string> cols;
        cols.reserve(4);
        std::stringstream ss(line);
        std::string item;
        while (std::getline(ss, item, ';')) {
            cols.push_back(item);
        }
        if (cols.size() < 4) continue; // ignora linhas incompletas

        MaterialDTO m;
        m.nome         = detail::trim(cols[0]);
        m.valor        = detail::parse_br_double(cols[1]);
        m.largura      = detail::parse_br_double(cols[2]);
        m.comprimento  = detail::parse_br_double(cols[3]);
        out.push_back(std::move(m));
    }
    return true;
}

// -------------------- Settings: carregar/salvar --------------------
inline Settings loadOrCreateSettings(const std::string& filename = "settings.json") {
    Settings s;
    const std::string p = dataPath(filename);

    // tenta ler
    {
        std::ifstream f(p);
        if (f) {
            try {
                json j; f >> j;
                s = j.get<Settings>();
                return s;
            } catch (...) {
                // cai na criação/overwrite de default
            }
        }
    }

    // grava default
    try {
        json j = s;
        atomicWrite(fs::path(p), j.dump(2));
    } catch (...) {}
    return s;
}

inline bool saveSettings(const Settings& s, const std::string& filename = "settings.json") {
    const std::string p = dataPath(filename);
    try {
        json j = s;
        return atomicWrite(fs::path(p), j.dump(2));
    } catch (const std::exception& e) {
        wr::p("PERSIST", p + " exception: " + e.what(), "Red");
        return false;
    } catch (...) {
        wr::p("PERSIST", p + " unknown exception", "Red");
        return false;
    }
}

} // namespace Persist
