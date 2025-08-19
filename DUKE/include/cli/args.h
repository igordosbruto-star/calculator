#pragma once

// ----------------------------------------------------------
// Estruturas e funções para argumentos de linha de comando
// ----------------------------------------------------------
#include <string>
#include <vector>
namespace duke {

// Comandos reconhecidos pela aplicação (ainda não implementados)
enum class Comando {
    Nenhum,   // nenhum comando informado
    Criar,    // criar recursos
    Listar,   // listar recursos
    Comparar  // comparar dados
};

struct CliOptions {
    bool showHelp = false;       // exibir ajuda
    bool autoMode = false;       // modo automático
    std::string projeto;         // caminho para o projeto
    std::string tipo;            // tipo de material
    std::string ordem;           // ordem de listagem
    std::vector<int> ids;        // ids informados para comparação
    Comando comando = Comando::Nenhum; // comando solicitado
    std::vector<std::string> naoMapeados; // argumentos não reconhecidos
    bool ok = true;             // falso se houve tokens não mapeados
};

// Processa argc/argv e devolve opções reconhecidas
// Exemplo de uso:
//   CliOptions opt = parseArgs(argc, argv);
//   if (!opt.ok) return 1; // argumentos inválidos
CliOptions parseArgs(int argc, char* argv[]);

} // namespace duke
