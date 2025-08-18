#include <cassert>
#include <filesystem>
#include "core/persist.h"
#include <cstdlib>

// Testa dataPath com diretório padrão, ambiente e parâmetro explícito
void test_data_path() {
    // Uso de struct de configuração
    Persist::Config cfg; cfg.baseDir = "tmpdata";
    Persist::setConfig(cfg);
    const std::string p = Persist::dataPath("dummy.txt");
    assert(p == "tmpdata/dummy.txt");
    assert(std::filesystem::exists("tmpdata"));

    // Uso de variável de ambiente
    setenv("PERSIST_BASE_DIR", "envdata", 1);
    Persist::setConfig(Persist::Config::fromEnv());
    const std::string p2 = Persist::dataPath("dummy2.txt");
    assert(p2 == "envdata/dummy2.txt");
    assert(std::filesystem::exists("envdata"));

    // Parâmetro explícito
    const std::string p3 = Persist::dataPath("dummy3.txt", "paramdata");
    assert(p3 == "paramdata/dummy3.txt");
    assert(std::filesystem::exists("paramdata"));
}
