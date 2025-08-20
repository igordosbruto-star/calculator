#pragma once

#include <string>
#include <nlohmann/json.hpp>
#include "core/paths.h"
#include "core/atomic_write.h"

struct Settings {
    int         decimal_places = 2;
    std::string prefer         = "ask";
};

inline void to_json(nlohmann::json& j, const Settings& s) {
    j = nlohmann::json{
        {"decimal_places", s.decimal_places},
        {"prefer", s.prefer}
    };
}

inline void from_json(const nlohmann::json& j, Settings& s) {
    if (j.contains("decimal_places")) j.at("decimal_places").get_to(s.decimal_places);
    if (j.contains("prefer")) j.at("prefer").get_to(s.prefer);
}

namespace Persist {

Settings loadOrCreateSettings(const std::string& filename = "settings.json",
                              const std::string& baseDir = config().baseDir);
bool saveSettings(const Settings& s, const std::string& filename = "settings.json",
                  const std::string& baseDir = config().baseDir);

} // namespace Persist
