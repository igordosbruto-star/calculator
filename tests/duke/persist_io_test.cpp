#include "core/persist.h"
#include <vector>
#include <cassert>
#include <filesystem>

// Testa ciclo de importação e exportação em JSON e CSV
void test_persist_io() {
    std::vector<MaterialDTO> itens{{"Madeira", 10.0, 2.0, 3.0}};

    // Salva e carrega JSON
    assert(Persist::saveJSON("teste_io.json", itens));
    std::vector<MaterialDTO> carregado;
    int schemaVersion = 0;
    assert(Persist::loadJSON("teste_io.json", carregado, &schemaVersion));
    assert(schemaVersion == 1);
    assert(carregado.size() == 1);
    assert(carregado[0].nome == "Madeira");
    assert(carregado[0].tipo == "linear");

    // Salva e carrega CSV
    assert(Persist::saveCSV("teste_io.csv", itens));
    carregado.clear();
    assert(Persist::loadCSV("teste_io.csv", carregado));
    assert(carregado.size() == 1);
    assert(carregado[0].valor == 10.0);
    assert(carregado[0].tipo == "linear");

    // Limpa arquivos de teste
    std::filesystem::remove("data/teste_io.json");
    std::filesystem::remove("data/teste_io.csv");
}
