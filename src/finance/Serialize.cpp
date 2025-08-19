#include "finance/Serialize.h"

#include <stdexcept>

namespace finance {

std::string to_string(Tipo t) {
    switch (t) {
    case Tipo::Compra: return "Compra";
    case Tipo::Vendas: return "Vendas";
    case Tipo::Outros: return "Outros";
    case Tipo::Contas: return "Contas";
    case Tipo::Investimento: return "Investimento";
    case Tipo::Cofrinho: return "Cofrinho";
    }
    throw std::invalid_argument("Tipo invalido");
}

Tipo tipo_from_string(const std::string& s) {
    if (s == "Compra") return Tipo::Compra;
    if (s == "Vendas") return Tipo::Vendas;
    if (s == "Outros") return Tipo::Outros;
    if (s == "Contas") return Tipo::Contas;
    if (s == "Investimento") return Tipo::Investimento;
    if (s == "Cofrinho") return Tipo::Cofrinho;
    throw std::invalid_argument("tipo_from_string: " + s);
}

void to_json(json& j, const Lancamento& l) {
    j = json{
        {"id", l.id},
        {"tipo", to_string(l.tipo)},
        {"subtipo", l.subtipo},
        {"descricao", l.descricao},
        {"valor", l.valor},
        {"moeda", l.moeda},
        {"data", l.data},
        {"entrada", l.entrada},
        {"projeto_id", l.projeto_id},
        {"conta", l.conta},
        {"tags", l.tags}
    };
}

void from_json(const json& j, Lancamento& l) {
    std::string tipo_str;
    j.at("id").get_to(l.id);
    j.at("tipo").get_to(tipo_str);
    l.tipo = tipo_from_string(tipo_str);
    j.at("subtipo").get_to(l.subtipo);
    if (j.contains("descricao"))
        j.at("descricao").get_to(l.descricao);
    else
        l.descricao.clear();
    j.at("valor").get_to(l.valor);
    j.at("moeda").get_to(l.moeda);
    j.at("data").get_to(l.data);
    j.at("entrada").get_to(l.entrada);
    if (j.contains("projeto_id"))
        j.at("projeto_id").get_to(l.projeto_id);
    else
        l.projeto_id.clear();
    if (j.contains("conta"))
        j.at("conta").get_to(l.conta);
    else
        l.conta.clear();
    if (j.contains("tags"))
        j.at("tags").get_to(l.tags);
    else
        l.tags.clear();
}

} // namespace finance

