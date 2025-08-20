#pragma once

#include "cli/args.h"

namespace duke {

// Inicia a aplicação interativa.
void iniciarAplicacao(bool autoMode);

// Processa comandos de linha de comando.
int processarComando(const CliOptions& opt);

} // namespace duke

