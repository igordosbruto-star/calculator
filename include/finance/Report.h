#pragma once

#include <iosfwd>
#include <string>

#include "finance/Repo.h"

namespace finance {

// Gera relatório mensal.
// Imprime tabela em `out` e exporta CSV para `out/finance/<ano>-<mes>-report.csv`.
// Retorna o caminho do arquivo CSV criado.
std::string reportMes(const FinanceRepo& repo, int ano, int mes, std::ostream& out);

} // namespace finance

