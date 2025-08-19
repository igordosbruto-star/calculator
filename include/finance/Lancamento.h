#pragma once

#include <string>
#include <vector>

#include "finance/Tipos.h"

namespace finance {

// Representa um lançamento financeiro individual
struct Lancamento {
    std::string id;                  // "FIN-2025-08-18-0001"
    Tipo tipo;                       // enum principal
    std::string subtipo;             // "insumos", "salario", etc.
    std::string descricao;           // opcional
    double valor;                    // >0
    std::string moeda;               // "BRL"
    std::string data;                // ISO "2025-08-18"
    bool entrada;                    // true=recebível, false=saída
    std::string projeto_id;          // opcional
    std::string conta;               // "caixa", "banco", ...
    std::vector<std::string> tags;   // ["maca", "cliente_x"]
};

} // namespace finance

