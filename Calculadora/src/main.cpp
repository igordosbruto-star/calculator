// ==========================================
// Arquivo: main.cpp
// Descrição: Ponto de entrada minimalista
// ==========================================

#include "Debug.h"
#include "App.h"
#include "cli.h"

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

    // Se for solicitado help, exibe instruções e sai
    if (opt.showHelp) {
        std::cout << "Uso: ./app [--auto] [--help]\n";
        std::cout << "  --auto : calcula usando o material mais barato.\n";
        std::cout << "  --help : mostra esta ajuda e finaliza.\n";
        return 0;
    }

    wr::p("MAIN", "Iniciando..", "Green");
    std::cout << "\n";

    App app;
    app.iniciar(opt.autoMode);

    std::cout << "\n";
    wr::p("MAIN", "Finalizando..", "Green");
    return 0;
}
#endif // UNIT_TEST
