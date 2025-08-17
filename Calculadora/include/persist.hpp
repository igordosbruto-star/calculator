#pragma once

#include <string>
#include "plano_corte.h"

namespace Persist {

// ------------------------------------------------------------
// Retorna data/hora atual no formato ISO8601 "YYYY-MM-DDTHH:MM:SS".
// Exemplo:
//   std::string s = Persist::nowIso8601();
// ------------------------------------------------------------
std::string nowIso8601();

// ----------------------------------------------------------------------
// Gera identificador com timestamp e projeto: "YYYY-MM-DD_HHMMSS_<projeto>".
// Espaços e caracteres não alfanuméricos são substituídos por '_'.
// Exemplo:
//   std::string id = Persist::makeId("Meu Projeto");
// ----------------------------------------------------------------------
std::string makeId(const std::string& projeto);

// ----------------------------------------------------------------------
// Garante existência da pasta "out/planos/<id>" e retorna o caminho.
// O parâmetro `id` deve ser o retorno de `makeId`.
// Exemplo:
//   std::string dir = Persist::outPlanosDirFor("Meu Projeto", id);
// ----------------------------------------------------------------------
std::string outPlanosDirFor(const std::string& projeto, const std::string& id);

// ----------------------------------------------------------------------
// Salva um PlanoCorteDTO em JSON no arquivo "plano.json" dentro de `dir`.
// Utiliza escrita atômica para evitar corrupção em caso de falha.
// Exemplo:
//   Persist::savePlanoJSON("out/planos/xyz", plano);
// ----------------------------------------------------------------------
bool savePlanoJSON(const std::string& dir, const PlanoCorteDTO& plano);

// ----------------------------------------------------------------------
// Salva um PlanoCorteDTO em CSV no arquivo "plano.csv" dentro de `dir`.
// Cabeçalho: "nome;largura_m;comprimento_m;porm2;area_m2;valor;rot90".
// Números são formatados com vírgula decimal.
// Exemplo:
//   Persist::savePlanoCSV("out/planos/xyz", plano);
// ----------------------------------------------------------------------
bool savePlanoCSV(const std::string& dir, const PlanoCorteDTO& plano);

// ----------------------------------------------------------------------
// Atualiza o arquivo de índice global "out/planos/index.json".
// Se já existir entrada com mesmo `id`, ela é substituída.
// Cria o arquivo caso não exista, usando escrita atômica.
// Exemplo:
//   Persist::updateIndex(plano);
// ----------------------------------------------------------------------
bool updateIndex(const PlanoCorteDTO& plano);

} // namespace Persist

