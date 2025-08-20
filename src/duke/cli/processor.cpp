#include <iostream>

#include "duke/duke.hpp"
#include "cli/App.h"
#include "core/Debug.h"
#include "ApplicationCore.h"
#include "finance/Serialize.h"

namespace duke {

void iniciarAplicacao(bool autoMode) {
    App app;
    app.iniciar(autoMode);
}

int processarComando(const CliOptions& opt) {
    if (opt.showHelp) {
        std::cout << "Uso: ./app [comando] [opcoes]\n";
        std::cout << "  comandos: criar, listar, comparar (em construcao)\n";
        std::cout << "  --auto : calcula usando o material mais barato.\n";
        std::cout << "  --projeto <arq> : abre projeto informado.\n";
        std::cout << "  --tipo <t> : filtra por tipo de material.\n";
        std::cout << "  --ordem <c:d> : ordena listagem.\n";
        std::cout << "  --ids <1,2,3> : ids para comparacao.\n";
        std::cout << "  --help : mostra esta ajuda e finaliza.\n";
        if (opt.finCmd != FinCmd::None) {
            std::cout << "\nFinanceiro:\n";
            std::cout << "  fin add --tipo=<Tipo> --valor=<V> --data=<AAAA-MM-DD> (--entrada|--saida)"
                         " [--subtipo=<Sub> --desc=<txt>]\n";
            std::cout << "    Tipos: Compra, Vendas, Outros, Contas, Investimento, Cofrinho.\n";
            std::cout << "    Subtipos sugeridos: insumos, ferramenta, salario, energia, recebiveis.\n";
        }
        return 0;
    }

    if (!opt.ok) {
        return 1;
    }

    if (opt.finCmd != FinCmd::None) {
        ApplicationCore core;
        core.carregarFinanceiro();
        if (opt.finCmd == FinCmd::Add) {
            if (!opt.finTipo) {
                wr::p("FIN", "--tipo obrigatorio", "Red");
                return 1;
            }
            if (!opt.finValor || *opt.finValor <= 0.0) {
                wr::p("FIN", "--valor deve ser >0", "Red");
                return 1;
            }
            if (opt.finData.empty()) {
                wr::p("FIN", "--data obrigatoria (AAAA-MM-DD)", "Red");
                return 1;
            }
            if (opt.finSubtipo.empty()) {
                wr::p("FIN", "Subtipo recomendado. Veja --help para sugestoes", "Yellow");
            }
            finance::Lancamento l;
            l.id = core.proximoIdLancamento();
            l.tipo = *opt.finTipo;
            l.subtipo = opt.finSubtipo;
            l.descricao = opt.finDesc;
            l.valor = *opt.finValor;
            l.moeda = "BRL";
            l.data = opt.finData;
            l.entrada = opt.finEntrada.value_or(true);
            if (!core.adicionarLancamento(l)) {
                wr::p("FIN", "Lancamento invalido", "Red");
                return 1;
            }
            std::cout << "Lancamento " << l.id << " salvo.\n";
        } else if (opt.finCmd == FinCmd::List) {
            finance::Filtro f;
            f.tipo = opt.finTipo;
            if (!opt.finSubtipo.empty()) f.subtipo = opt.finSubtipo;
            if (opt.finEntrada) f.entrada = opt.finEntrada;
            if (!opt.finDtIni.empty()) f.dt_ini = opt.finDtIni;
            if (!opt.finDtFim.empty()) f.dt_fim = opt.finDtFim;
            auto itens = core.listarLancamentos(f);
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
            double total = core.somarLancamentos(f);
            std::cout << total << "\n";
        }
        return 0;
    }

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

    iniciarAplicacao(opt.autoMode);

    std::cout << "\n";
    wr::p("MAIN", "Finalizando..", "Green");
    return 0;
}

} // namespace duke

