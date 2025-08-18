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
#include <system_error>
#include "core/Debug.h"

namespace fs = std::filesystem;

// Nota: todas as medidas de largura e comprimento permanecem em metros.
// ---- DTO de Material (somente dados base) ----
struct MaterialDTO {
    std::string nome;
    double valor = 0.0;      // valor total da peça
    double largura = 0.0;    // largura em metros
    double comprimento = 0.0; // comprimento em metros
    std::string tipo = "linear"; // unitario | linear | cubico
};

// ------------ JSON ------------
#include <nlohmann/json.hpp>
using nlohmann::json;

inline void to_json(json& j, const MaterialDTO& m) {
    j = json{
        {"nome", m.nome},
        {"tipo", m.tipo},
        {"valor", m.valor},
        {"largura", m.largura},
        {"comprimento", m.comprimento}
    };
}

inline void from_json(const json& j, MaterialDTO& m) {
    j.at("nome").get_to(m.nome);
    if (j.contains("tipo"))
        j.at("tipo").get_to(m.tipo);
    else
        m.tipo = "linear"; // migração para arquivos antigos
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

// ------------------------------------------------
// Valida MaterialDTO: nome nao vazio e valores >=0
// Exemplo:
//   MaterialDTO m{"Madeira", 10, 2, 3};
//   bool ok = Persist::validar(m); // true
// ------------------------------------------------
inline bool validar(const MaterialDTO& m) {
    if (m.nome.empty()) return false;
    if (m.valor < 0) return false;
    if (m.largura < 0) return false;
    if (m.comprimento < 0) return false;
    if (m.tipo != "unitario" && m.tipo != "linear" && m.tipo != "cubico") return false;
    return true;
}

// ----------------------------------------------
// Garante a pasta data/ e devolve "data/<arquivo>"
// Exemplo:
//   std::string p = Persist::dataPath("materiais.json"); // "data/materiais.json"
// ----------------------------------------------
inline std::string dataPath(const std::string& filename) {
    std::error_code ec;
    bool created = fs::create_directory("data", ec);
    if (ec) {
        wr::p("PERSIST", std::string("data create fail: ") + ec.message(), "Red");
    } else if (created) {
        wr::p("PERSIST", "Diretorio data criado.", "Green");
    }
    return "data/" + filename;
}

// ----------------------------------------------
// Escrita atômica com .tmp e backup .bak
// Exemplo:
//   Persist::atomicWrite("data/arquivo.txt", "conteudo");
// ----------------------------------------------
inline bool atomicWrite(const fs::path& finalPath, const std::string& content) {
    try {
        if (!finalPath.parent_path().empty()) {
            std::error_code ecDir;
            bool dirCreated = fs::create_directories(finalPath.parent_path(), ecDir);
            if (ecDir) {
                wr::p("PERSIST", finalPath.parent_path().string() + " create fail: " + ecDir.message(), "Red");
                return false;
            } else if (dirCreated) {
                wr::p("PERSIST", finalPath.parent_path().string() + " criado.", "Green");
            }
        }

        bool existed = fs::exists(finalPath);
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
        if (existed) {
            std::error_code ec;
            fs::copy_file(finalPath, bakPath, fs::copy_options::overwrite_existing, ec);
            if (ec) {
                wr::p("PERSIST", finalPath.string() + " backup copy fail: " + ec.message(), "Yellow");
            }
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

        wr::p("PERSIST", finalPath.string() + (existed ? " atualizado." : " criado."), "Green");
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
namespace mater {
// Atualiza JSON de materiais para versão mais recente
inline bool upgradeIfNeeded(json& j) {
    bool upgraded = false;
    if (!j.contains("schema_version")) {
        int v = 1;
        if (j.contains("version")) v = j["version"].get<int>();
        j["schema_version"] = v;
        j.erase("version");
        upgraded = true;
    }
    if (!j.contains("materiais") || !j["materiais"].is_array()) {
        j["materiais"] = json::array();
        upgraded = true;
    }
    for (auto& item : j["materiais"]) {
        if (!item.contains("tipo") || !item["tipo"].is_string() || item["tipo"].get<std::string>().empty()) {
            item["tipo"] = "linear";
            upgraded = true;
        }
    }
    return upgraded;
}
} // namespace mater

// Salva materiais em JSON com versão de schema
// Exemplo:
//   Persist::saveJSON("materiais.json", v);
inline bool saveJSON(const std::string& path, const std::vector<MaterialDTO>& v, int schemaVersion = 1) {
    for (const auto& m : v) {
        if (!validar(m)) {
            wr::p("PERSIST", "Material invalido: " + m.nome, "Red");
            return false;
        }
    }
    json j;
    j["schema_version"] = schemaVersion;
    j["materiais"]      = v; // usa to_json automaticamente
    return atomicWrite(fs::path(dataPath(path)), j.dump(2));
}

// Carrega materiais de JSON, migrando campos antigos se necessário
// Exemplo:
//   std::vector<MaterialDTO> itens;
//   Persist::loadJSON("materiais.json", itens);
inline bool loadJSON(const std::string& path, std::vector<MaterialDTO>& out, int* out_schema_version = nullptr) {
    const std::string p = dataPath(path);
    std::ifstream f(p);
    if (!f) {
        wr::p("PERSIST", p + " open fail", "Red");
        return false;
    }
    try {
        json j; f >> j;
        bool migrated = mater::upgradeIfNeeded(j);
        int schemaVersion = j.value("schema_version", 1);
        if (out_schema_version) *out_schema_version = schemaVersion;
        if (j.contains("materiais") && j["materiais"].is_array()) {
            out.clear();
            for (const auto& item : j["materiais"]) {
                out.push_back(item.get<MaterialDTO>());
            }
            if (migrated) {
                atomicWrite(fs::path(p), j.dump(2));
            }
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
    for (const auto& m : items) {
        if (!validar(m)) {
            wr::p("PERSIST", "Material invalido: " + m.nome, "Red");
            return false;
        }
    }

    std::ostringstream oss;

    // Cabeçalho com tipo
    oss << "nome;tipo;valor;largura;comprimento\n";

    for (const auto& m : items) {
        // Sanitize simples para não quebrar CSV com ';'
        std::string safe = m.nome;
        for (auto& ch : safe) if (ch == ';') ch = ',';

        // Números com vírgula decimal (compatível com Planilhas em localidade Brasil)
        oss << safe << ';'
            << m.tipo << ';'
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

    // Lê primeira linha (cabeçalho). Esperado: nome;tipo;valor;largura;comprimento
    if (!std::getline(f, line)) {
        wr::p("PERSIST", p + " header read fail", "Red");
        return false;
    }

    while (std::getline(f, line)) {
        if (line.empty()) continue;

        // Split por ';'
        std::vector<std::string> cols;
        cols.reserve(5);
        std::stringstream ss(line);
        std::string item;
        while (std::getline(ss, item, ';')) {
            cols.push_back(item);
        }
        if (cols.size() < 5) continue; // ignora linhas incompletas

        MaterialDTO m;
        m.nome         = detail::trim(cols[0]);
        m.tipo         = detail::trim(cols[1]);
        if (m.tipo.empty()) m.tipo = "linear";
        m.valor        = detail::parse_br_double(cols[2]);
        m.largura      = detail::parse_br_double(cols[3]);
        m.comprimento  = detail::parse_br_double(cols[4]);
        out.push_back(std::move(m));
    }
    return true;
}

// -------------------- Settings: carregar/salvar --------------------
namespace sett {
// Atualiza JSON de settings para versão mais recente
inline bool upgradeIfNeeded(json& j) {
    bool upgraded = false;
    if (!j.contains("schema_version")) {
        j["schema_version"] = 1;
        upgraded = true;
    }
    if (!j.contains("decimal_places")) { j["decimal_places"] = 2; upgraded = true; }
    if (!j.contains("prefer")) { j["prefer"] = "ask"; upgraded = true; }
    return upgraded;
}
} // namespace sett

// Exemplo:
//   Settings s = Persist::loadOrCreateSettings();
inline Settings loadOrCreateSettings(const std::string& filename = "settings.json") {
    Settings s;
    const std::string p = dataPath(filename);

    // tenta ler
    {
        std::ifstream f(p);
        if (f) {
            try {
                json j; f >> j;
                bool up = sett::upgradeIfNeeded(j);
                s = j.get<Settings>();
                if (up) atomicWrite(fs::path(p), j.dump(2));
                return s;
            } catch (...) {
                // cai na criação/overwrite de default
            }
        }
    }

    // grava default
    try {
        json j = s;
        j["schema_version"] = 1;
        atomicWrite(fs::path(p), j.dump(2));
    } catch (...) {}
    return s;
}

// Exemplo:
//   Persist::saveSettings(s);
inline bool saveSettings(const Settings& s, const std::string& filename = "settings.json") {
    const std::string p = dataPath(filename);
    try {
        json j = s;
        j["schema_version"] = 1;
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
