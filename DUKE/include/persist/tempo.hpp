#pragma once

#include <string>
#include <vector>
#include "domain/Tempo.h"
namespace calculadora {

namespace Persist {

// Carrega template de operações de data/templates/tempos/<nome>.json
// Exemplo:
//   std::vector<Operacao> ops;
//   Persist::loadTempoTemplate("padrao", ops);
bool loadTempoTemplate(const std::string& nome, std::vector<Operacao>& out);

} // namespace Persist

} // namespace calculadora
