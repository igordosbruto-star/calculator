#include "persist/tempo.hpp"
#include "persist.h"

#include <filesystem>
#include <fstream>

using nlohmann::json;
namespace fs = std::filesystem;

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
        out = j.value("operacoes", std::vector<Operacao>{});
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

