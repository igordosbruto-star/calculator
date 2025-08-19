#include <cassert>
#include <regex>
#include <filesystem>
#include "persist.hpp"

void test_persist_helpers() {
    // Testa formato ISO8601
    const std::string iso = Persist::nowIso8601();
    const std::regex isoRe{"\\d{4}-\\d{2}-\\d{2}T\\d{2}:\\d{2}:\\d{2}"};
    assert(std::regex_match(iso, isoRe));

    // Testa makeId
    const std::string id = Persist::makeId("Projeto X");
    const std::regex idRe{"\\d{4}-\\d{2}-\\d{2}_\\d{6}_projeto_x"};
    assert(std::regex_match(id, idRe));

    // Testa criação do diretório
    const std::string dir = Persist::outPlanosDirFor("Projeto X", id);
    assert(std::filesystem::exists(dir));
}

