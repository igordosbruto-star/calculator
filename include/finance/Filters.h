#pragma once

#include <optional>
#include <string>
#include <vector>

#include "finance/Tipos.h"

namespace finance {

// Estrutura de filtros para consultas de lançamentos
struct Filtro {
    std::optional<Tipo> tipo;              // filtra por tipo principal
    std::optional<std::string> subtipo;    // filtra por subtipo
    std::optional<std::string> conta;      // filtra por conta
    std::optional<std::string> dt_ini;     // data inicial inclusiva
    std::optional<std::string> dt_fim;     // data final inclusiva
    std::optional<bool> entrada;           // true=entradas, false=saídas
    std::vector<std::string> tags_all;     // todas as tags (AND)
};

} // namespace finance

