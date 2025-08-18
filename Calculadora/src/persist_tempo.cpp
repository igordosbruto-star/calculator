#include "persist/tempo.hpp"
#include "core/persist.h"

#include <filesystem>
#include <fstream>

using nlohmann::json;
namespace fs = std::filesystem;

// Atualiza JSON de template de tempo se necessário
static bool upgradeIfNeeded(json& j) {
    bool upgraded = false;
    if (!j.contains("schema_version")) {
        j["schema_version"] = 1;
        upgraded = true;
    }
    if (!j.contains("operacoes") || !j["operacoes"].is_array()) {
        j["operacoes"] = json::array();
        upgraded = true;
    }
    return upgraded;
}

namespace Persist {

bool loadTempoTemplate(const std::string& nome, std::vector<Operacao>& out) {
    try {
        const fs::path p = fs::path(dataPath("templates/tempos/" + nome + ".json"));
        std::ifstream f(p);
        if (!f) {
            wr::p("PERSIST", p.string() + " open fail", "Red");
            return false;
        }
        json j; f >> j;
        bool up = upgradeIfNeeded(j);
        out = j.value("operacoes", std::vector<Operacao>{});
        if (up) atomicWrite(p, j.dump(2));
        return true;
    } catch (const std::exception& e) {
        wr::p("PERSIST", std::string("loadTempoTemplate exception: ") + e.what(), "Red");
        return false;
    } catch (...) {
        wr::p("PERSIST", "loadTempoTemplate unknown exception", "Red");
        return false;
    }
}

} // namespace Persist

