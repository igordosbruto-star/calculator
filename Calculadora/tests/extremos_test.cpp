#include "App.h"
#include "Material.h"
#include <vector>
#include <cassert>

// Inclui implementação para acessar extremosPorM2
#include "../src/App.cpp"

// Testa a comparação de materiais pelo valor por metro quadrado
void test_extremos() {
    std::vector<Material> mats;
    mats.emplace_back("Barato", 10.0, 1.0, 1.0);   // R$10 por m²
    mats.emplace_back("Caro", 50.0, 1.0, 1.0);     // R$50 por m²
    mats.emplace_back("Medio", 30.0, 2.0, 1.0);    // R$15 por m²

    Como r = extremosPorM2(mats);
    assert(r.menor.nome == "Barato");
    assert(r.maior.nome == "Caro");
}
