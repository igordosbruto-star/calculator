#include "duke.hpp"
#include <cassert>

// Testa cálculo simplificado do valor de corte
void test_calculadora_api() {
    Material m{"Madeira", 100.0, 2.0, 2.0};
    double valor = calcularValorCorte(m, 1.0, 0.5);
    assert(valor == 12.5);
}

