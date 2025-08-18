#include "Corte.h"
#include <cassert>

// Testa cálculo de área e valor do corte
void test_corte() {
    Corte c{"Peça", 2.0, 3.0, 10.0};
    assert(c.capArea() == 6.0);
    assert(c.capValor() == 60.0);
}
