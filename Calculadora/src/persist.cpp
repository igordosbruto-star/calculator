#include "persist.hpp"

#include <chrono>
#include <ctime>
#include <iomanip>
#include <sstream>
#include <cctype>
#include <filesystem>
#include <algorithm>

namespace fs = std::filesystem;

namespace Persist {

std::string nowIso8601() {
    const auto now = std::chrono::system_clock::now();
    const std::time_t t = std::chrono::system_clock::to_time_t(now);
    std::tm tm{}; 
#ifdef _WIN32
    localtime_s(&tm, &t);
#else
    localtime_r(&t, &tm);
#endif
    std::ostringstream oss;
    oss << std::put_time(&tm, "%Y-%m-%dT%H:%M:%S");
    return oss.str();
}

static std::string sanitize(const std::string& s) {
    std::string out; out.reserve(s.size());
    for (unsigned char ch : s) {
        if (std::isalnum(ch)) out.push_back(static_cast<char>(std::tolower(ch)));
        else if (ch == ' ') out.push_back('_');
        else out.push_back('_');
    }
    return out;
}

std::string makeId(const std::string& projeto) {
    std::string iso = nowIso8601();
    for (auto& ch : iso) {
        if (ch == 'T') ch = '_';
    }
    iso.erase(std::remove(iso.begin(), iso.end(), ':'), iso.end());
    return iso + "_" + sanitize(projeto);
}

std::string outPlanosDirFor(const std::string& projeto, const std::string& id) {
    (void)projeto; // id já contém o nome do projeto
    const fs::path dir = fs::path("out") / "planos" / id;
    try {
        fs::create_directories(dir);
    } catch (...) {
        // falha silenciosa: retorno mesmo assim
    }
    return dir.string();
}

} // namespace Persist

