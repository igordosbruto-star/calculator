#include "duke/plano_corte.h"
#include <nlohmann/json.hpp>
#include <cassert>

// Testa ida e volta de CorteDTO e PlanoCorteDTO via to_json/from_json
void test_plano_dto() {
    // ---- CorteDTO ----
    CorteDTO c{"Lateral", 2.0, 0.15, 180.0, 0.3, 54.0, true};

    nlohmann::json jc;
    to_json(jc, c);
    assert(jc["nome"] == "Lateral");
    assert(jc["rot90"] == true);

    CorteDTO c2{};
    from_json(jc, c2);
    assert(c2.nome == c.nome);
    assert(c2.largura_m == c.largura_m);
    assert(c2.comprimento_m == c.comprimento_m);
    assert(c2.porm2 == c.porm2);
    assert(c2.area_m2 == c.area_m2);
    assert(c2.valor == c.valor);
    assert(c2.rot90 == c.rot90);

    // ---- PlanoCorteDTO ----
    PlanoCorteDTO p;
    p.id = "2025-08-17_1830_Maca_80x200";
    p.projeto = "Maca_80x200";
    p.gerado_em = "2025-08-17T18:30:12-03:00";
    p.algoritmo = "simples";
    p.porm2_usado = 180.0;
    p.cortes.push_back(c);
    p.total_area_m2 = 0.3;
    p.total_valor = 54.0;

    nlohmann::json jp;
    to_json(jp, p);
    assert(jp["id"] == p.id);
    assert(jp["cortes"].is_array());
    assert(jp["cortes"][0]["nome"] == "Lateral");

    PlanoCorteDTO p2{};
    from_json(jp, p2);
    assert(p2.id == p.id);
    assert(p2.projeto == p.projeto);
    assert(p2.cortes.size() == 1);
    assert(p2.cortes[0].nome == "Lateral");
    assert(p2.total_valor == p.total_valor);
}
