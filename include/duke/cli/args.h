#pragma once

// ----------------------------------------------------------
// Estruturas e funções para argumentos de linha de comando
// ----------------------------------------------------------
#include <string>
#include <vector>
#include <optional>
#include "finance/Tipos.h"
#include "duke/error.h"
namespace duke {

// Comandos reconhecidos pela aplicação (ainda não implementados)
enum class Comando {
    Nenhum,   // nenhum comando informado
    Criar,    // criar recursos
    Listar,   // listar recursos
    Comparar  // comparar dados
};

// Subcomandos para o módulo financeiro
enum class FinCmd {
    None,
    Add,
    List,
    Sum
};

struct CliOptions {
    bool showHelp = false;       // exibir ajuda
    bool autoMode = false;       // modo automático
    std::string projeto;         // caminho para o projeto
    std::string tipo;            // tipo de material
    std::string ordem;           // ordem de listagem
    std::vector<int> ids;        // ids informados para comparação
    Comando comando = Comando::Nenhum; // comando solicitado
    FinCmd finCmd = FinCmd::None; // comando financeiro
    std::optional<finance::Tipo> finTipo; // tipo de lançamento
    std::string finSubtipo;      // subtipo
    std::optional<double> finValor; // valor
    std::string finData;         // data do lançamento
    std::string finDesc;         // descrição
    std::optional<bool> finEntrada; // entrada ou saída
    std::string finDtIni;        // filtro data inicial
    std::string finDtFim;        // filtro data final
    std::vector<duke::ErrorDetail> errors; // lista de erros encontrados
};

// Processa argc/argv e devolve opções reconhecidas
// Exemplo de uso:
//   CliOptions opt = parseArgs(argc, argv);
//   if (!opt.errors.empty()) return 1; // argumentos inválidos
CliOptions parseArgs(int argc, char* argv[]);

} // namespace duke
