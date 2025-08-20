#include "core/MaterialDTO.h"
#include "core/paths.h"
#include <cassert>
#include <filesystem>

void test_persist_load_save() {
    std::filesystem::remove_all("tmp_persist");
    Persist::Config cfg; cfg.baseDir = "tmp_persist";
    Persist::setConfig(cfg);

    std::vector<MaterialDTO> itens = {
        {"Madeira", 100.0, 2.0, 3.0, "linear"},
        {"Aco", 200.0, 1.0, 4.0, "linear"}
    };

    assert(Persist::saveJSON("materiais.json", itens));
    std::vector<MaterialDTO> out;
    assert(Persist::loadJSON("materiais.json", out));
    assert(out.size() == itens.size());
    assert(out[0].nome == itens[0].nome);

    std::vector<MaterialDTO> dummy;
    assert(!Persist::loadJSON("inexistente.json", dummy));
    std::vector<MaterialDTO> invalido{{"", -1.0, 1.0, 1.0, "linear"}};
    assert(!Persist::saveJSON("invalido.json", invalido));

    assert(Persist::saveXML("materiais.xml", itens));
    out.clear();
    assert(Persist::loadXML("materiais.xml", out));
    assert(out.size() == itens.size());

    out.clear();
    assert(!Persist::loadXML("inexistente.xml", out));
    assert(!Persist::saveXML("invalido.xml", invalido));
}

