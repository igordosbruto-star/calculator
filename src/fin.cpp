#include <iostream>
#include <string>

#include "finance/Report.h"

using finance::FinanceRepo;

int main(int argc, char* argv[]) {
    if (argc < 5) {
        std::cerr << "Uso: fin report mes --ano=AAAA --mes=MM\n";
        return 1;
    }

    std::string cmd1 = argv[1];
    std::string cmd2 = argv[2];
    if (cmd1 != "report" || cmd2 != "mes") {
        std::cerr << "Uso: fin report mes --ano=AAAA --mes=MM\n";
        return 1;
    }

    int ano = 0;
    int mes = 0;
    for (int i = 3; i < argc; ++i) {
        std::string arg = argv[i];
        if (arg.rfind("--ano=", 0) == 0)
            ano = std::stoi(arg.substr(6));
        else if (arg.rfind("--mes=", 0) == 0)
            mes = std::stoi(arg.substr(6));
    }
    if (ano == 0 || mes == 0) {
        std::cerr << "Ano ou mês inválido\n";
        return 1;
    }

    FinanceRepo repo;
    repo.load();
    finance::reportMes(repo, ano, mes, std::cout);
    return 0;
}

