#include "duke/ApplicationCore.h"
#include <cassert>
#include <filesystem>
#include <stdexcept>
#include "core/persist.h"

void test_application_core() {
    using namespace duke;
    std::filesystem::remove_all("tmp_appcore");
    Persist::Config cfg; cfg.baseDir = "tmp_appcore";
    Persist::setConfig(cfg);
    std::vector<MaterialDTO> itens = {
        {"Madeira", 100.0, 2.0, 3.0, "linear"},
        {"Aco", 200.0, 1.0, 4.0, "linear"}
    };
    Persist::save("materiais.json", itens);

    ApplicationCore core;
    std::vector<MaterialDTO> base;
    std::vector<Material> mats;
    assert(core.carregar(base, mats));
    auto lista = core.listarMateriais(base);
    assert(lista.size() == 2);
    auto comps = core.compararMateriais(mats, {0, 1});
    assert(comps.size() == 2);
    bool menor = false, maior = false;
    for (const auto& c : comps) {
        if (c.menor) menor = true;
        if (c.maior) maior = true;
    }
    assert(menor && maior);

    bool threw = false;
    try {
        core.compararMateriais(mats, {0, 2});
    } catch (const std::out_of_range&) {
        threw = true;
    }
    assert(threw);

    std::vector<MaterialDTO> single = {
        {"Madeira", 100.0, 2.0, 3.0, "linear"}
    };
    Persist::save("materiais.json", single);
    base.clear();
    mats.clear();
    assert(!core.carregar(base, mats));
}
