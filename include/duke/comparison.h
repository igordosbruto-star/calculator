#pragma once

#include <string>
#include <vector>
#include "Material.h"

namespace duke::comparison {

struct MaterialComparado {
    std::string nome;
    double porm2 = 0.0;
    bool menor = false;
    bool maior = false;
};

struct Selecionados {
    std::vector<Material> materiais;
    std::vector<int> indices; // 0-based
};

Selecionados selecionarMateriais(const std::string& ids,
                                 const std::vector<Material>& mats);
std::vector<Material> selecionarMateriais(const std::vector<int>& ids,
                                          const std::vector<Material>& mats);
std::vector<MaterialComparado> compararMateriais(
    const std::vector<Material>& matsSelecionados);

} // namespace duke::comparison

