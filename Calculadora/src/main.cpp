// ==========================================
// Arquivo: main.cpp
// Descrição: Ponto de entrada minimalista
// ==========================================

#include "Debug.h"
#include "App.h"
#include "cli.h"
#include <string>

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
        std::cout << "Uso: ./app [comando] [opcoes]\n";
        std::cout << "  comandos: abrir, listar, comparar (em construcao)\n";
        std::cout << "  --auto : calcula usando o material mais barato.\n";
        std::cout << "  --projeto <arq> : abre projeto informado.\n";
        std::cout << "  --help : mostra esta ajuda e finaliza.\n";
        return 0;
    }

    // Se houver comando, apenas registra placeholder
    if (opt.comando != Comando::Nenhum) {
        std::string nome;
        switch (opt.comando) {
            case Comando::Abrir: nome = "abrir"; break;
            case Comando::Listar: nome = "listar"; break;
            case Comando::Comparar: nome = "comparar"; break;
            default: nome = ""; break;
        }
        wr::p("MAIN", "Comando '" + nome + "' ainda nao implementado.", "Yellow");
        return 0;
    }

    if (!opt.projeto.empty()) {
        wr::p("MAIN", "Projeto informado: " + opt.projeto, "Blue");
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
