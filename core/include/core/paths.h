#pragma once

#include <filesystem>
#include <string>
#include "core/Debug.h"

namespace Persist {

namespace fs = std::filesystem;

struct Config {
    std::string baseDir = "data";
    static Config fromEnv();
};

Config& config();
void setConfig(const Config& cfg);
std::string dataPath(const std::string& filename, const std::string& baseDir = config().baseDir);

} // namespace Persist
