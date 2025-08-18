#include "custo/EstimadorCusto.h"
#include "domain/MaterialUnitario.h"
#include "domain/MaterialLinear.h"
#include "domain/MaterialCubico.h"
#include <cassert>

// Testa o EstimadorCusto com diferentes tipos de materiais
void test_estimador_custo() {
    EstimadorCusto est;

    // Material unitário
    MaterialUnitario mu(5.0);
    ItemReq reqU{"MAT-U", "unitario", 3.0, {}};
    double custoU = est.custoMaterial(reqU, mu);
    assert(custoU == 15.0);

    // Material linear com perda interna de 10%
    MaterialLinear ml(10.0, 0.1);
    ItemReq reqL{"MAT-L", "linear", 4.0, {0.0, 0.0, 0.0, 2.0}};
    double custoL = est.custoMaterial(reqL, ml);
    assert(custoL == 88.0);

    // Material cúbico
    MaterialCubico mc(100.0);
    Medidas m3{2.0, 0.5, 1.0, 0.0};
    ItemReq reqC{"MAT-C", "cubico", 3.0, m3};
    double custoC = est.custoMaterial(reqC, mc);
    assert(custoC == 300.0);

    // Projeto agregando os três itens
    ProjetoCusto prj;
    prj.materiais.push_back({reqU, &mu});
    prj.materiais.push_back({reqL, &ml});
    prj.materiais.push_back({reqC, &mc});

    CustoParams cfg{0.05, 0.1, 0.2, 2};
    double total = est.custoProjeto(prj, cfg);
    assert(total == 558.56);
}

