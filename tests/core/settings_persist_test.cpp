#include "core/Settings.h"
#include <cassert>
#include <filesystem>

void test_settings_persist() {
    std::filesystem::remove_all("tmp_settings");
    Persist::Config cfg; cfg.baseDir = "tmp_settings"; Persist::setConfig(cfg);
    Settings s; s.decimal_places = 3; s.prefer = "cheapest";
    assert(Persist::saveSettings(s));
    Settings loaded = Persist::loadOrCreateSettings();
    assert(loaded.decimal_places == 3);
    assert(loaded.prefer == "cheapest");
    std::filesystem::remove_all("tmp_settings");
}
