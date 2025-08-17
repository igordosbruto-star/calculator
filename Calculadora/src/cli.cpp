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
        } else if (a == "--projeto" && i + 1 < argc) {
            // consome próximo argumento como caminho do projeto
            opt.projeto = argv[++i];
        } else if (opt.comando == Comando::Nenhum) {
            // registra comando principal
            if (a == "abrir") {
                opt.comando = Comando::Abrir;
            } else if (a == "listar") {
                opt.comando = Comando::Listar;
            } else if (a == "comparar") {
                opt.comando = Comando::Comparar;
            }
        }
    }
    return opt;
}

