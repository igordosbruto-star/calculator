// ==========================================
// Arquivo: main.cpp
// Descrição: Ponto de entrada minimalista
// ==========================================

#include "core/Debug.h"
#include "cli/App.h"
#include "cli/args.h"
#include <string>
#include "finance/Repo.h"
#include "finance/Serialize.h"

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

    // Encerra se houver argumentos desconhecidos
    if (!opt.ok) {
        return 1;
    }

    // Comandos financeiros diretos
    if (opt.finCmd != FinCmd::None) {
        finance::FinanceRepo repo;
        repo.load();
        if (opt.finCmd == FinCmd::Add) {
            finance::Lancamento l;
            l.id = repo.nextId();
            l.tipo = opt.finTipo.value_or(finance::Tipo::Outros);
            l.subtipo = opt.finSubtipo;
            l.descricao = opt.finDesc;
            l.valor = opt.finValor.value_or(0.0);
            l.moeda = "BRL";
            l.data = opt.finData;
            l.entrada = opt.finEntrada.value_or(true);
            repo.add(l);
            repo.save();
            std::cout << "Lancamento " << l.id << " salvo.\n";
        } else if (opt.finCmd == FinCmd::List) {
            finance::Filtro f;
            f.tipo = opt.finTipo;
            if (!opt.finSubtipo.empty()) f.subtipo = opt.finSubtipo;
            if (opt.finEntrada) f.entrada = opt.finEntrada;
            if (!opt.finDtIni.empty()) f.dt_ini = opt.finDtIni;
            if (!opt.finDtFim.empty()) f.dt_fim = opt.finDtFim;
            auto itens = repo.query(f);
            for (const auto& l : itens) {
                std::cout << l.id << " | " << finance::to_string(l.tipo)
                          << " | " << l.subtipo << " | "
                          << (l.entrada?"+":"-") << l.valor
                          << " | " << l.data << " | " << l.descricao << "\n";
            }
        } else if (opt.finCmd == FinCmd::Sum) {
            finance::Filtro f;
            f.tipo = opt.finTipo;
            if (!opt.finSubtipo.empty()) f.subtipo = opt.finSubtipo;
            if (opt.finEntrada) f.entrada = opt.finEntrada;
            if (!opt.finDtIni.empty()) f.dt_ini = opt.finDtIni;
            if (!opt.finDtFim.empty()) f.dt_fim = opt.finDtFim;
            double total = repo.sum(f);
            std::cout << total << "\n";
        }
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
