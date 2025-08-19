#include <finance/Lancamento.h>
#include <finance/Filters.h>
#include <cassert>

using namespace finance;

void test_lancamento() {
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

    assert(l.tipo == Tipo::Compra);
    assert(!l.entrada);
    assert(l.tags.size() == 1);
}

void test_filtro() {
    Filtro f;
    assert(!f.tipo);
    f.tipo = Tipo::Vendas;
    f.tags_all = {"cliente_x"};
    assert(f.tipo == Tipo::Vendas);
    assert(f.tags_all[0] == "cliente_x");
}

