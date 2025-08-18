#include "core/persist.h"
#include <cassert>

// Testa Persist::validar para tipos de material
void testValidarMaterialPorTipo() {
    // Tipos válidos
    MaterialDTO unit{"U", 1.0, 0.0, 0.0, "unitario"};
    MaterialDTO lin{"L", 1.0, 0.0, 0.0, "linear"};
    MaterialDTO cub{"C", 1.0, 0.0, 0.0, "cubico"};
    assert(Persist::validar(unit));
    assert(Persist::validar(lin));
    assert(Persist::validar(cub));

    // Tipo inválido
    MaterialDTO inv{"X", 1.0, 0.0, 0.0, "foo"};
    assert(!Persist::validar(inv));
}
