#include "core/persist.h"
#include "duke/error.h"
#include <cassert>

void test_persist_validar_message() {
    MaterialDTO inv{"A", 1.0, 0.0, 0.0, "foo"};
    duke::ErrorDetail err = Persist::validar(inv);
    assert(err.code == duke::ErrorCode::InvalidType);
    assert(duke::errorMessage(err.code, err.field) == "tipo: tipo invalido");
}
