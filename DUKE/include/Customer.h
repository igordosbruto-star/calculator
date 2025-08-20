#pragma once

#include <string>
#include <nlohmann/json.hpp>

namespace duke {

// Representa um cliente do sistema de vendas.
class Customer {
public:
    std::string nome; // nome do cliente

    Customer() = default;
    explicit Customer(const std::string& n);
};

// Serialização para JSON
inline void to_json(nlohmann::json& j, const Customer& c) {
    j = nlohmann::json{{"nome", c.nome}};
}

inline void from_json(const nlohmann::json& j, Customer& c) {
    j.at("nome").get_to(c.nome);
}

} // namespace duke

