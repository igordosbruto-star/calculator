#pragma once

#include <string>

namespace finance {

// Representa um fornecedor cadastrado
struct Supplier {
    std::string id;       // identificador único
    std::string nome;     // nome do fornecedor
    std::string contato;  // informações de contato
};

} // namespace finance

