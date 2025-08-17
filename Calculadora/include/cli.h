#pragma once

// ----------------------------------------------------------
// Estruturas e funções para argumentos de linha de comando
// ----------------------------------------------------------
struct CliOptions {
    bool showHelp = false; // exibir ajuda
    bool autoMode = false; // modo automático
};

// Processa argc/argv e devolve opções reconhecidas
// Exemplo de uso:
//   CliOptions opt = parseArgs(argc, argv);
CliOptions parseArgs(int argc, char* argv[]);

