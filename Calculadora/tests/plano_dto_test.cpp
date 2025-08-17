#include "plano_corte.h"
#include <nlohmann/json.hpp>
#include <cassert>

// Testa ida e volta via JSON para CorteDTO e PlanoCorteDTO
void test_plano_dto() {
    // monta um corte
    CorteDTO c{"Lateral", 2.0, 0.15, 180.0, 0.3, 54.0, true};

    // serializa e desserializa
    nlohmann::json j = c;
    CorteDTO c2 = j.get<CorteDTO>();
    assert(c2.nome == "Lateral");
    assert(c2.rot90 == true);
    assert(c2.valor == 54.0);

    // monta plano com o corte
    PlanoCorteDTO p;
    p.id = "2025-08-17_1830_Maca_80x200";
    p.projeto = "Maca_80x200";
    p.gerado_em = "2025-08-17T18:30:12-03:00";
    p.algoritmo = "simples";
    p.porm2_usado = 180.0;
    p.cortes.push_back(c);
    p.total_area_m2 = 0.3;
    p.total_valor = 54.0;

    // round trip
    nlohmann::json pj = p;
    PlanoCorteDTO p2 = pj.get<PlanoCorteDTO>();
    assert(p2.id == p.id);
    assert(p2.cortes.size() == 1);
    assert(p2.cortes[0].nome == "Lateral");
    assert(p2.total_valor == 54.0);
}

