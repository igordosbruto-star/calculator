#include "core/MaterialDTO.h"
#include <cassert>

// Testa validacao antes de salvar materiais
void test_persist() {
    MaterialDTO invalido{"", -1.0, 1.0, 1.0};
    std::vector<MaterialDTO> itens{invalido};

    // Deve falhar ao tentar salvar JSON e CSV
    assert(!Persist::saveJSON("invalido.json", itens));
    assert(!Persist::saveCSV("invalido.csv", itens));

    MaterialDTO ok{"Madeira", 10.0, 2.0, 3.0};
    itens = {ok};

    // Agora deve salvar com sucesso
    assert(Persist::saveJSON("ok.json", itens));
    assert(Persist::saveCSV("ok.csv", itens));
}

