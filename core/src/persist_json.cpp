#include "core/persist.h"
#include <nlohmann/json.hpp>

using nlohmann::json;

namespace Persist {

bool saveJSON(const std::string& path, const std::vector<MaterialDTO>& v,
              int schemaVersion, const std::string& baseDir) {
    for (const auto& m : v) {
        auto err = validar(m);
        if (err.code != duke::ErrorCode::Ok) {
            wr::p("PERSIST", duke::errorMessage(err.code, err.field) + ": " + m.nome, "Red");
            return false;
        }
    }
    json j;
    j["schema_version"] = schemaVersion;
    j["materiais"] = v;
    return atomicWrite(fs::path(dataPath(path, baseDir)), j.dump(2));
}

bool loadJSON(const std::string& path, std::vector<MaterialDTO>& out,
              int* out_schema_version, const std::string& baseDir) {
    const std::string p = dataPath(path, baseDir);
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

} // namespace Persist

