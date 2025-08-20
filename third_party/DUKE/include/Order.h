#pragma once

#include <string>
#include <nlohmann/json.hpp>

namespace duke {

// Representa um pedido simples de venda.
class Order {
public:
    int id = 0;            // identificador do pedido
    std::string cliente;   // nome do cliente
    std::string item;      // produto solicitado
    int quantidade = 0;    // quantidade de itens

    Order() = default;
    Order(int i, std::string c, std::string it, int q);
};

// Serialização para JSON
inline void to_json(nlohmann::json& j, const Order& o) {
    j = nlohmann::json{{"id", o.id}, {"cliente", o.cliente}, {"item", o.item}, {"quantidade", o.quantidade}};
}

inline void from_json(const nlohmann::json& j, Order& o) {
    j.at("id").get_to(o.id);
    j.at("cliente").get_to(o.cliente);
    j.at("item").get_to(o.item);
    j.at("quantidade").get_to(o.quantidade);
}

} // namespace duke

