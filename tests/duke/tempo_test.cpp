#include "duke/domain/Tempo.h"
#include "duke/persist/tempo.hpp"
#include "core/persist.h"
#include <cassert>
#include <filesystem>

void test_tempo() {
    Operacao op{Fase::Preparo, 0.5, 4};
    assert(Tempo::tempoItem(op) == 2.0);

    std::vector<Operacao> ops{op};
    assert(Tempo::tempoProjeto(ops) == 2.0);

    // Teste de template
    nlohmann::json j;
    j["operacoes"] = ops;
    auto path = ::Persist::dataPath("templates/tempos/teste.json");
    ::Persist::atomicWrite(std::filesystem::path(path), j.dump());
    std::vector<Operacao> carregadas;
    assert(duke::Persist::loadTempoTemplate("teste", carregadas));
    assert(carregadas.size() == 1);
    assert(Tempo::tempoProjeto(carregadas) == 2.0);
}
