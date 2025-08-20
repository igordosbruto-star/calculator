#include "duke/persist.hpp"
#include "duke/plano_corte.h"
#include "duke/Corte.h"
#include <cassert>
#include <fstream>
#include <filesystem>

// Testa salvamento e recarga de plano em JSON e CSV
void test_plano_io() {
    namespace fs = std::filesystem;
    fs::remove_all("out");

    // monta um corte e seu DTO correspondente
    Corte c("Lateral", 2.0, 0.15, 180.0);
    CorteDTO dto{"Lateral", 2.0, 0.15, 180.0, c.getArea(), c.getValor(), false};

    // monta plano com o corte
    PlanoCorteDTO p;
    p.projeto = "ProjetoX";
    p.algoritmo = "simples";
    p.porm2_usado = 180.0;
    p.cortes.push_back(dto);
    p.total_area_m2 = c.getArea();
    p.total_valor = c.getValor();
    p.gerado_em = Persist::nowIso8601();
    p.id = Persist::makeId(p.projeto);

    const std::string dir = Persist::outPlanosDirFor(p.projeto, p.id);

    // salva e lê JSON
    assert(Persist::savePlanoJSON(dir, p));
    PlanoCorteDTO p2;
    assert(Persist::loadPlanoJSON(dir + "/plano.json", p2));
    assert(p2.cortes.size() == 1);
    assert(p2.cortes[0].nome == "Lateral");
    assert(p2.total_valor == p.total_valor);

    // salva e lê CSV
    assert(Persist::savePlanoCSV(dir, p));
    std::ifstream cf(dir + "/plano.csv");
    assert(cf);
    std::string header; std::getline(cf, header);
    assert(header == "nome;largura_m;comprimento_m;porm2;area_m2;valor;rot90");
    std::string line; std::getline(cf, line);
    assert(line.find("Lateral") == 0);
    assert(line.find(",") != std::string::npos); // números com vírgula

    fs::remove_all("out");
}
