#include "domain/MaterialFactory.h"
#include <cassert>

// Testa MaterialFactory::fromDTO
void test_material_factory() {
    // unitario
    MaterialDTO du{"ItemU", 5.0, 0.0, 0.0, "unitario"};
    auto mu = MaterialFactory::fromDTO(du);
    assert(mu->tipo() == "unitario");

    // linear
    MaterialDTO dl{"ItemL", 10.0, 0.0, 0.0, "linear"};
    auto ml = MaterialFactory::fromDTO(dl);
    assert(ml->tipo() == "linear");

    // cubico
    MaterialDTO dc{"ItemC", 100.0, 0.0, 0.0, "cubico"};
    auto mc = MaterialFactory::fromDTO(dc);
    assert(mc->tipo() == "cubico");

    // tipo invalido
    MaterialDTO di{"Inv", 1.0, 0.0, 0.0, "foo"};
    bool errou = false;
    try {
        auto bad = MaterialFactory::fromDTO(di);
        (void)bad;
    } catch (const std::invalid_argument&) {
        errou = true;
    }
    assert(errou);
}
