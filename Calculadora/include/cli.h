#pragma once

// ----------------------------------------------------------
// Estruturas e funções para argumentos de linha de comando
// ----------------------------------------------------------
#include <string>

// Comandos reconhecidos pela aplicação (ainda não implementados)
enum class Comando {
    Nenhum,   // nenhum comando informado
    Abrir,    // abrir projeto existente
    Listar,   // listar recursos
    Comparar  // comparar dados
};

struct CliOptions {
    bool showHelp = false; // exibir ajuda
    bool autoMode = false; // modo automático
    std::string projeto;   // caminho para o projeto
    Comando comando = Comando::Nenhum; // comando solicitado
};

// Processa argc/argv e devolve opções reconhecidas
// Exemplo de uso:
//   CliOptions opt = parseArgs(argc, argv);
CliOptions parseArgs(int argc, char* argv[]);

