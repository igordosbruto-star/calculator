#include <cassert>
#include <filesystem>
#include "core/persist.h"

// Testa que dataPath cria o diretório `data` e retorna o caminho correto
void test_data_path() {
    const std::string p = Persist::dataPath("dummy.txt");
    assert(p == "data/dummy.txt");
    assert(std::filesystem::exists("data"));
}
