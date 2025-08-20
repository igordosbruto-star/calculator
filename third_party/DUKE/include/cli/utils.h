#pragma once

#include <vector>
#include "core.h"
#include "persist.hpp"

namespace duke::cli {

// Exibe materiais cadastrados
// Exemplo:
//   duke::cli::listarMateriais(base);
void listarMateriais(const std::vector<MaterialDTO>& base);

// Reconstrói vetor de Materiais e persiste base
// Exemplo:
//   duke::cli::salvarReconstruir(base, mats);
void salvarReconstruir(std::vector<MaterialDTO>& base, std::vector<Material>& mats);

} // namespace duke::cli

