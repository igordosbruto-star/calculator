// ==========================================
// Arquivo: main.cpp
// Descrição: Ponto de entrada minimalista
// ==========================================

#include "core/Debug.h"
#include "cli/args.h"
#include "duke/duke.hpp"
#include <string>

using namespace duke;

// ----------------------------------------------------------
// Entrada principal da aplicação
// Processa argumentos e executa o App
// Exemplo de uso:
//   ./app --auto
//   ./app --help
// ----------------------------------------------------------
#ifndef UNIT_TEST
int main(int argc, char* argv[]) {
    // Interpreta opções da linha de comando
    CliOptions opt = parseArgs(argc, argv);
    if (!opt.errors.empty()) {
        return static_cast<int>(opt.errors.front().code);
    }
    // Processa comandos através da interface pública
    return processarComando(opt);
}
#endif // UNIT_TEST
