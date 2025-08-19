#include <finance/Serialize.h>
#include <cassert>
#include <nlohmann/json.hpp>

using namespace finance;
using nlohmann::json;

void test_tipo_string() {
    assert(to_string(Tipo::Compra) == "Compra");
    assert(to_string(Tipo::Vendas) == "Vendas");
    assert(tipo_from_string("Contas") == Tipo::Contas);
}

void test_serialize() {
    Lancamento l{
        "FIN-2025-08-18-0001",
        Tipo::Compra,
        "insumos",
        "TNT rolo",
        129.9,
        "BRL",
        "2025-08-18",
        false,
        "",
        "caixa",
        {"maca"}
    };

    json j = l;
    Lancamento l2 = j.get<Lancamento>();
    assert(l2.id == l.id);
    assert(l2.tipo == l.tipo);
    assert(l2.tags.size() == 1 && l2.tags[0] == "maca");
}

