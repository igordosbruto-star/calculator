#include "Corte.h"
#include <cassert>

// Testa cálculo de área e valor do corte
void test_corte() {
    Corte c{"Peça", 2.0, 3.0, 10.0};
    assert(c.getArea() == 6.0);
    assert(c.getValor() == 60.0);
}
