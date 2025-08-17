#pragma once

#include <string>

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

} // namespace Persist

