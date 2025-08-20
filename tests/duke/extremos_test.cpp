#include "duke/core.h"
#include "duke/Material.h"
#include <vector>
#include <cassert>
#include <stdexcept>


// Testa a comparação de materiais pelo valor por metro quadrado
void test_extremos() {
    std::vector<Material> mats;
    mats.emplace_back("Barato", 10.0, 1.0, 1.0);   // R$10 por m²
    mats.emplace_back("Caro", 50.0, 1.0, 1.0);     // R$50 por m²
    mats.emplace_back("Medio", 30.0, 2.0, 1.0);    // R$15 por m²

    core::Como r = core::extremosPorM2(mats);
    assert(r.menor.nome == "Barato");
    assert(r.maior.nome == "Caro");
}

// Garante que uma lista vazia gera exceção
void test_extremos_vazio() {
    std::vector<Material> mats;
    bool houveExcecao = false;
    try {
        core::extremosPorM2(mats);
    } catch (const std::invalid_argument&) {
        houveExcecao = true;
    }
    assert(houveExcecao);
}
