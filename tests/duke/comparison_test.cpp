#include "duke/comparison.h"
#include <cassert>
#include "core.h"

void test_comparison() {
    std::vector<MaterialDTO> base = {
        {"Madeira", 100.0, 2.0, 3.0, "linear"},
        {"Aco", 200.0, 1.0, 4.0, "linear"}
    };
    auto mats = duke::core::reconstruirMateriais(base);

    // caso valido
    auto sel = duke::comparison::selecionarMateriais("1 2", mats);
    auto comps = duke::comparison::compararMateriais(sel.materiais);
    assert(comps.size() == 2);
    bool menor = false, maior = false;
    for (const auto& c : comps) {
        if (c.menor) menor = true;
        if (c.maior) maior = true;
    }
    assert(menor && maior);

    // id invalido
    bool threw = false;
    try {
        duke::comparison::selecionarMateriais("1 3", mats);
    } catch (const std::out_of_range&) {
        threw = true;
    }
    assert(threw);

    // ids insuficientes
    threw = false;
    try {
        duke::comparison::selecionarMateriais("1", mats);
    } catch (const std::invalid_argument&) {
        threw = true;
    }
    assert(threw);

    // token nao numerico
    threw = false;
    try {
        duke::comparison::selecionarMateriais("1 a", mats);
    } catch (const std::invalid_argument&) {
        threw = true;
    }
    assert(threw);

    // indice duplicado
    threw = false;
    try {
        duke::comparison::selecionarMateriais("1 1", mats);
    } catch (const std::invalid_argument&) {
        threw = true;
    }
    assert(threw);
}
