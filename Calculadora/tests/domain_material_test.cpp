#include "domain/MaterialUnitario.h"
#include "domain/MaterialLinear.h"
#include "domain/MaterialCubico.h"
#include <cassert>

// Testa as subclasses de MaterialBase
void test_domain_material() {
    // Material unitario
    MaterialUnitario mu(5.0);
    assert(mu.tipo() == "unitario");
    assert(mu.custo(3, Medidas{}) == 15.0);

    // Material linear com 10% de perda
    MaterialLinear ml(10.0, 0.1);
    Medidas m1;
    m1.comprimento = 2.0;
    double custoLinear = ml.custo(4, m1);
    assert(ml.tipo() == "linear");
    assert(custoLinear == 88.0);

    // Material cubico
    MaterialCubico mc(100.0);
    Medidas m2;
    m2.largura = 2.0;
    m2.altura = 0.5;
    m2.profundidade = 1.0;
    double custoCubico = mc.custo(3, m2);
    assert(mc.tipo() == "cubico");
    assert(custoCubico == 300.0);
}
