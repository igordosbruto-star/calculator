#include "persist.hpp"
#include "plano_corte.h"
#include <nlohmann/json.hpp>
#include <cassert>
#include <fstream>
#include <filesystem>

// Testa salvamento e leitura imediata de plano em JSON e CSV
void test_plano_persist_io() {
    // monta um corte simples
    CorteDTO c{"Lateral", 2.0, 0.15, 180.0, 0.3, 54.0, false};

    // monta plano com o corte
    PlanoCorteDTO p;
    p.id = "plano_teste";
    p.projeto = "ProjetoX";
    p.gerado_em = "2025-08-17T18:30:12";
    p.algoritmo = "simples";
    p.porm2_usado = 180.0;
    p.cortes.push_back(c);
    p.total_area_m2 = 0.3;
    p.total_valor = 54.0;

    const std::string dir = Persist::outPlanosDirFor(p.projeto, p.id);

    // salva e lê JSON
    assert(Persist::savePlanoJSON(dir, p));
    std::ifstream jf(dir + "/plano.json");
    assert(jf);
    nlohmann::json j; jf >> j;
    PlanoCorteDTO p2 = j.get<PlanoCorteDTO>();
    assert(p2.cortes.size() == 1);
    assert(p2.cortes[0].nome == "Lateral");

    // salva e lê CSV
    assert(Persist::savePlanoCSV(dir, p));
    std::ifstream cf(dir + "/plano.csv");
    assert(cf);
    std::string header; std::getline(cf, header);
    assert(header == "nome;largura_m;comprimento_m;porm2;area_m2;valor;rot90");
    std::string line; std::getline(cf, line);
    assert(line.find(".") == std::string::npos); // números com vírgula
    assert(line.find("Lateral") == 0);

    std::filesystem::remove_all(dir);
}
