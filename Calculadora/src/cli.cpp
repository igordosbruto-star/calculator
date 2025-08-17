// ==========================================
// Arquivo: cli.cpp
// Descrição: Tratamento simples de argumentos
// ==========================================

#include "cli.h"
#include <string>

CliOptions parseArgs(int argc, char* argv[]) {
    CliOptions opt; // guarda opções reconhecidas
    for (int i = 1; i < argc; ++i) {
        std::string a = argv[i];
        if (a == "--help" || a == "-h") {
            opt.showHelp = true;
        } else if (a == "--auto") {
            opt.autoMode = true;
        }
    }
    return opt;
}

