#include "core/Settings.h"
#include <fstream>

using nlohmann::json;

namespace Persist {

namespace sett {
static bool upgradeIfNeeded(json& j) {
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

Settings loadOrCreateSettings(const std::string& filename, const std::string& baseDir) {
    Settings s;
    const std::string p = dataPath(filename, baseDir);

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
            }
        }
    }

    try {
        json j = s;
        j["schema_version"] = 1;
        atomicWrite(fs::path(p), j.dump(2));
    } catch (...) {}
    return s;
}

bool saveSettings(const Settings& s, const std::string& filename, const std::string& baseDir) {
    const std::string p = dataPath(filename, baseDir);
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
