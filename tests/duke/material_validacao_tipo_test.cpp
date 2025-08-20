#include "core/MaterialDTO.h"
#include "duke/Material.h"
#include "duke/error.h"
#include <cassert>
#include <stdexcept>

using duke::ErrorCode;

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

    // Setters devem lançar para valores negativos
    Material m{"Mat", 10.0, 2.0, 3.0};

    m.setValor(20.0);
    assert(m.getValor() == 20.0);

    bool errou = false;
    try {
        m.setValor(-1.0);
    } catch (const std::invalid_argument&) {
        errou = true;
    }
    assert(errou);

    errou = false;
    try {
        m.setLarg(-1.0);
    } catch (const std::invalid_argument&) {
        errou = true;
    }
    assert(errou);

    errou = false;
    try {
        m.setComp(-1.0);
    } catch (const std::invalid_argument&) {
        errou = true;
    }
    assert(errou);
}
