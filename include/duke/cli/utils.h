#pragma once

#include <vector>
#include <string>
#include "core.h"
#include "persist.hpp"

namespace duke::cli {

// Exibe materiais cadastrados
// Exemplo:
//   duke::cli::listarMateriais(base);
void listarMateriais(const std::vector<MaterialDTO>& base);

// Lê um índice de material válido (1..n) e retorna a posição (0..n-1)
// Exemplo:
//   size_t idx = duke::cli::readMaterialIndex(base, "Indice: ");
size_t readMaterialIndex(const std::vector<MaterialDTO>& base, const std::string& prompt);

// Reconstrói vetor de Materiais e persiste base
// Exemplo:
//   duke::cli::salvarReconstruir(base, mats);
void salvarReconstruir(std::vector<MaterialDTO>& base, std::vector<Material>& mats);

} // namespace duke::cli

