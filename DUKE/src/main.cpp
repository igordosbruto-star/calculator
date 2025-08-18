// ==========================================
// Arquivo: main.cpp
// Descrição: Ponto de entrada minimalista
// ==========================================

#include "core/Debug.h"
#include "cli/App.h"
#include "cli/args.h"
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

    // Se for solicitado help, exibe instruções e sai
    if (opt.showHelp) {
        std::cout << "Uso: ./app [comando] [opcoes]\n";
        std::cout << "  comandos: criar, listar, comparar (em construcao)\n";
        std::cout << "  --auto : calcula usando o material mais barato.\n";
        std::cout << "  --projeto <arq> : abre projeto informado.\n";
        std::cout << "  --tipo <t> : filtra por tipo de material.\n";
        std::cout << "  --ordem <c:d> : ordena listagem.\n";
        std::cout << "  --ids <1,2,3> : ids para comparacao.\n";
        std::cout << "  --help : mostra esta ajuda e finaliza.\n";
        return 0;
    }

    // Se houver comando, apenas registra placeholder
    if (opt.comando != Comando::Nenhum) {
        std::string nome;
        switch (opt.comando) {
            case Comando::Criar: nome = "criar"; break;
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
