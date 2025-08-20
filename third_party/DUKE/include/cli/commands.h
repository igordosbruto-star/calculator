#pragma once

#include <vector>
#include "cli/utils.h"

namespace duke::cli {

// Adiciona novo material
// Exemplo:
//   duke::cli::adicionarMaterial(base, mats);
void adicionarMaterial(std::vector<MaterialDTO>& base, std::vector<Material>& mats);

// Edita material existente
// Exemplo:
//   duke::cli::editarMaterial(base, mats);
void editarMaterial(std::vector<MaterialDTO>& base, std::vector<Material>& mats);

// Remove material por indice
// Exemplo:
//   duke::cli::removerMaterial(base, mats);
void removerMaterial(std::vector<MaterialDTO>& base, std::vector<Material>& mats);

} // namespace duke::cli

