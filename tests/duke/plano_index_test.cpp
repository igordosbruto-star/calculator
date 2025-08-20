#include "duke/persist.hpp"
#include <nlohmann/json.hpp>
#include <filesystem>
#include <fstream>
#include <cassert>
#include <vector>

// Testa inserção e atualização do índice global de planos
void test_plano_index() {
    namespace fs = std::filesystem;

    // Garantir ambiente limpo
    fs::remove_all("out");

    // Plano 1
    PlanoCorteDTO p1;
    p1.id = "id1";
    p1.total_valor = 100.0;
    p1.total_area_m2 = 1.0;
    p1.porm2_usado = 100.0;

    // Plano 2
    PlanoCorteDTO p2;
    p2.id = "id2";
    p2.total_valor = 200.0;
    p2.total_area_m2 = 2.0;
    p2.porm2_usado = 200.0;

    // Insere dois planos
    assert(Persist::updateIndex(p1));
    assert(Persist::updateIndex(p2));

    // Lê índice e verifica entradas
    std::ifstream f("out/planos/index.json");
    assert(f);
    nlohmann::json j; f >> j;
    assert(j["planos"].size() == 2);
    bool ok1 = false, ok2 = false;
    for (const auto& item : j["planos"]) {
        if (item["id"] == p1.id) {
            assert(item["total_valor"].get<double>() == p1.total_valor);
            ok1 = true;
        }
        if (item["id"] == p2.id) {
            assert(item["total_area_m2"].get<double>() == p2.total_area_m2);
            ok2 = true;
        }
    }
    assert(ok1 && ok2);

    // Atualiza plano 1
    p1.total_valor = 150.0;
    assert(Persist::updateIndex(p1));

    std::ifstream f2("out/planos/index.json");
    nlohmann::json j2; f2 >> j2;
    assert(j2["planos"].size() == 2); // não duplica
    int count = 0;
    for (const auto& item : j2["planos"]) {
        if (item["id"] == p1.id) {
            assert(item["total_valor"].get<double>() == 150.0);
            count++;
        }
    }
    assert(count == 1);

    fs::remove_all("out");

    // Testa leitura via API
    assert(Persist::updateIndex(p1));
    assert(Persist::updateIndex(p2));
    std::vector<Persist::PlanoIndexEntry> entradas;
    assert(Persist::loadIndex(entradas));
    assert(entradas.size() == 2);
    assert(entradas[0].id == "id1" || entradas[1].id == "id1");
    fs::remove_all("out");
}

