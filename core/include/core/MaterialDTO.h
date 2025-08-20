#pragma once

#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <nlohmann/json.hpp>

#include "core/Debug.h"
#include "duke/error.h"
#include "core/paths.h"
#include "core/atomic_write.h"

struct MaterialDTO {
    std::string nome;
    double valor = 0.0;
    double largura = 0.0;
    double comprimento = 0.0;
    std::string tipo = "linear";
};

inline void to_json(nlohmann::json& j, const MaterialDTO& m) {
    j = nlohmann::json{
        {"nome", m.nome},
        {"tipo", m.tipo},
        {"valor", m.valor},
        {"largura", m.largura},
        {"comprimento", m.comprimento}
    };
}

inline void from_json(const nlohmann::json& j, MaterialDTO& m) {
    j.at("nome").get_to(m.nome);
    if (j.contains("tipo"))
        j.at("tipo").get_to(m.tipo);
    else
        m.tipo = "linear";
    j.at("valor").get_to(m.valor);
    j.at("largura").get_to(m.largura);
    j.at("comprimento").get_to(m.comprimento);
}

namespace Persist {

inline duke::ErrorDetail validar(const MaterialDTO& m) {
    if (m.nome.empty()) return {duke::ErrorCode::EmptyField, "nome"};
    if (m.valor < 0) return {duke::ErrorCode::NegativeValue, "valor"};
    if (m.largura < 0) return {duke::ErrorCode::NegativeValue, "largura"};
    if (m.comprimento < 0) return {duke::ErrorCode::NegativeValue, "comprimento"};
    if (m.tipo != "unitario" && m.tipo != "linear" && m.tipo != "cubico")
        return {duke::ErrorCode::InvalidType, "tipo"};
    return {duke::ErrorCode::Ok, ""};
}

inline std::string to_str_br(double x, int precision = 6) {
    std::ostringstream oss;
    oss.setf(std::ios::fixed);
    oss.precision(precision);
    oss << x;
    std::string s = oss.str();
    for (auto& ch : s) if (ch == '.') ch = ',';
    return s;
}

bool saveJSON(const std::string& path, const std::vector<MaterialDTO>& v,
              int schemaVersion = 1,
              const std::string& baseDir = config().baseDir);

bool loadJSON(const std::string& path, std::vector<MaterialDTO>& out,
              int* out_schema_version = nullptr,
              const std::string& baseDir = config().baseDir);

template <typename T>
bool saveJSONVec(const std::string& path, const std::vector<T>& v,
                 const std::string& key, int schemaVersion = 1,
                 const std::string& baseDir = config().baseDir) {
    nlohmann::json j;
    j["schema_version"] = schemaVersion;
    j[key] = v;
    return atomicWrite(fs::path(dataPath(path, baseDir)), j.dump(2));
}

template <typename T>
bool loadJSONVec(const std::string& path, std::vector<T>& out,
                 const std::string& key, int* out_schema_version = nullptr,
                 const std::string& baseDir = config().baseDir) {
    const std::string p = dataPath(path, baseDir);
    std::ifstream f(p);
    if (!f) {
        wr::p("PERSIST", p + " open fail", "Red");
        return false;
    }
    try {
        nlohmann::json j; f >> j;
        int schemaVersion = j.value("schema_version", 1);
        if (out_schema_version) *out_schema_version = schemaVersion;
        if (j.contains(key) && j[key].is_array()) {
            out = j[key].template get<std::vector<T>>();
            return true;
        }
        wr::p("PERSIST", p + " missing '" + key + "'", "Red");
        return false;
    } catch (const std::exception& e) {
        wr::p("PERSIST", p + " parse error: " + e.what(), "Red");
        return false;
    } catch (...) {
        wr::p("PERSIST", p + " unknown parse error", "Red");
        return false;
    }
}

bool saveCSV(const std::string& path, const std::vector<MaterialDTO>& items,
             const std::string& baseDir = config().baseDir);

bool loadCSV(const std::string& path, std::vector<MaterialDTO>& out,
             const std::string& baseDir = config().baseDir);

bool saveXML(const std::string& path, const std::vector<MaterialDTO>& items,
             const std::string& baseDir = config().baseDir);

bool loadXML(const std::string& path, std::vector<MaterialDTO>& out,
             const std::string& baseDir = config().baseDir);

bool save(const std::string& path, const std::vector<MaterialDTO>& v,
          int schemaVersion = 1,
          const std::string& baseDir = config().baseDir);

bool load(const std::string& path, std::vector<MaterialDTO>& out,
          int* out_schema_version = nullptr,
          const std::string& baseDir = config().baseDir);

} // namespace Persist
