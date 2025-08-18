# DUKE

API pública simplificada para cálculos de cortes.

## Uso

Inclua `include/calculadora.hpp` e utilize as funções disponibilizadas.

```cpp
#include "calculadora.hpp"

using namespace calculadora;

int main() {
    Material m{"Madeira", 100.0, 2.0, 2.0};
    double valor = calcularValorCorte(m, 1.0, 0.5);
    return 0;
}
```

`calcularValorCorte` retorna o custo do corte com base no preço por metro quadrado do material.
