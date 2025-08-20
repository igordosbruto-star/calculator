#include "core/MaterialDTO.h"
#include "core/paths.h"
#include "core/atomic_write.h"
#include <cassert>
#include <vector>
#include <filesystem>

// Testa migração ao carregar JSON antigo sem campo 'tipo'
void test_persist_migration() {
    const std::string filename = "legacy.json";
    const std::string legacy = "{\n  \"version\":1,\n  \"materiais\":[{\"nome\":\"Madeira\",\"valor\":10.0,\"largura\":2.0,\"comprimento\":3.0}]\n}";
    const std::string path = Persist::dataPath(filename);
    Persist::atomicWrite(path, legacy);

    std::vector<MaterialDTO> itens;
    assert(Persist::loadJSON(filename, itens));
    assert(itens.size() == 1);
    assert(itens[0].tipo == "linear"); // migração aplica padrão

    // carregar novamente para garantir que foi salvo com 'tipo'
    std::vector<MaterialDTO> again;
    assert(Persist::loadJSON(filename, again));
    assert(again[0].tipo == "linear");

    std::filesystem::remove("data/" + filename);
}
