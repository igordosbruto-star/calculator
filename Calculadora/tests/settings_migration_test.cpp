#include "persist.h"
#include <cassert>
#include <filesystem>
#include <fstream>
#include <nlohmann/json.hpp>

using nlohmann::json;

// Testa migração e schema_version em settings.json
void test_settings_migration() {
    const std::string filename = "legacy_settings.json";
    const std::string legacy = "{ \"decimal_places\": 4 }";
    const std::string path = Persist::dataPath(filename);
    Persist::atomicWrite(path, legacy);

    Settings s = Persist::loadOrCreateSettings(filename);
    assert(s.decimal_places == 4);
    assert(s.prefer == "ask");

    std::ifstream f(path);
    json j; f >> j;
    assert(j.contains("schema_version"));
    assert(j["schema_version"].get<int>() == 1);
    assert(std::filesystem::exists("data/" + filename + ".bak"));

    std::filesystem::remove("data/" + filename);
    std::filesystem::remove("data/" + filename + ".bak");
}
