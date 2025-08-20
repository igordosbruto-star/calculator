#include "core/paths.h"
#include <cstdlib>
#include <system_error>

namespace Persist {

Config Config::fromEnv() {
    Config c;
    if (const char* env = std::getenv("PERSIST_BASE_DIR")) {
        c.baseDir = env;
    }
    return c;
}

Config& config() {
    static Config cfg = Config::fromEnv();
    return cfg;
}

void setConfig(const Config& cfg) { config() = cfg; }

std::string dataPath(const std::string& filename, const std::string& baseDir) {
    std::error_code ec;
    bool created = fs::create_directories(baseDir, ec);
    if (ec) {
        wr::p("PERSIST", baseDir + " create fail: " + ec.message(), "Red");
    } else if (created) {
        wr::p("PERSIST", baseDir + " criado.", "Green");
    }
    return (fs::path(baseDir) / filename).string();
}

} // namespace Persist
