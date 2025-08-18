#pragma once

namespace duke::cli {

// Lê uma opção do usuário garantindo apenas 1 ou 2
// Exemplo:
//   int opt = duke::cli::lerOpcao12();
int lerOpcao12(int padrao = 1);

} // namespace duke::cli

