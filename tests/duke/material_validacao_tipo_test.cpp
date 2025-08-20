#include "core/persist.h"
#include <cassert>

// Testa Persist::validar para tipos de material
void testValidarMaterialPorTipo() {
    // Tipos válidos
    MaterialDTO unit{"U", 1.0, 0.0, 0.0, "unitario"};
    MaterialDTO lin{"L", 1.0, 0.0, 0.0, "linear"};
    MaterialDTO cub{"C", 1.0, 0.0, 0.0, "cubico"};
    assert(Persist::validar(unit).code == ErrorCode::Ok);
    assert(Persist::validar(lin).code == ErrorCode::Ok);
    assert(Persist::validar(cub).code == ErrorCode::Ok);

    // Tipo inválido
    MaterialDTO inv{"X", 1.0, 0.0, 0.0, "foo"};
    assert(Persist::validar(inv).code == ErrorCode::InvalidType);
}
