#include "persist.hpp"
#include "plano_corte.h"
#include "Corte.h"
#include <nlohmann/json.hpp>
#include <cassert>
#include <fstream>
#include <filesystem>

// Testa salvamento completo de plano em JSON, CSV e atualização do índice
void test_plano_persist_io() {
    namespace fs = std::filesystem;
    fs::remove_all("out");

    // monta um corte e seu DTO correspondente
    Corte c("Lateral", 2.0, 0.15, 180.0);
    CorteDTO dto{"Lateral", 2.0, 0.15, 180.0, c.capArea(), c.capValor(), false};

    // monta plano com o corte
    PlanoCorteDTO p;
    p.projeto = "ProjetoX";
    p.algoritmo = "simples";
    p.porm2_usado = 180.0;
    p.cortes.push_back(dto);
    p.total_area_m2 = c.capArea();
    p.total_valor = c.capValor();
    p.gerado_em = Persist::nowIso8601();
    p.id = Persist::makeId(p.projeto);

    const std::string dir = Persist::outPlanosDirFor(p.projeto, p.id);

    // salva e lê JSON
    assert(Persist::savePlanoJSON(dir, p));
    std::ifstream jf(dir + "/plano.json");
    assert(jf);
    nlohmann::json j; jf >> j;
    PlanoCorteDTO p2 = j.get<PlanoCorteDTO>();
    assert(p2.cortes.size() == 1);
    assert(p2.total_valor == p.total_valor);

    // salva e lê CSV
    assert(Persist::savePlanoCSV(dir, p));
    std::ifstream cf(dir + "/plano.csv");
    assert(cf);
    std::string header; std::getline(cf, header);
    assert(header == "nome;largura_m;comprimento_m;porm2;area_m2;valor;rot90");
    std::string line; std::getline(cf, line);
    assert(line.find(".") == std::string::npos); // números com vírgula
    assert(line.find("Lateral") == 0);

    // atualiza e verifica índice
    assert(Persist::updateIndex(p));
    std::ifstream idx("out/planos/index.json");
    assert(idx);
    nlohmann::json ji; idx >> ji;
    bool found = false;
    for (const auto& item : ji["planos"]) {
        if (item["id"].get<std::string>() == p.id) {
            found = true;
        }
    }
    assert(found);

    fs::remove_all("out");
}
