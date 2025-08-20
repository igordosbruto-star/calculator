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

    ApplicationCore core;
    std::vector<MaterialDTO> base;
    std::vector<Material> mats;
    // Carregamento padrão quando o arquivo não existe
    assert(core.carregar(base, mats));
    assert(base.size() == 2);
    assert(base[0].nome == "Pinus 20cm");
    assert(base[1].nome == "MDF 15mm");

    std::vector<MaterialDTO> itens = {
        {"Madeira", 100.0, 2.0, 3.0, "linear"},
        {"Aco", 200.0, 1.0, 4.0, "linear"}
    };
    Persist::save("materiais.json", itens);
    base.clear();
    mats.clear();
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

    // Verifica carregamento padrão via API de vendas
    std::filesystem::remove_all("tmp_appcore2");
    Persist::Config cfg2; cfg2.baseDir = "tmp_appcore2";
    Persist::setConfig(cfg2);
    ApplicationCore core2;
    assert(core2.carregar());
    auto estoque = core2.listarEstoque();
    assert(estoque.size() == 2);
    assert(estoque[0].nome == "Pinus 20cm");
    assert(estoque[1].nome == "MDF 15mm");

    Persist::setConfig({});
}
