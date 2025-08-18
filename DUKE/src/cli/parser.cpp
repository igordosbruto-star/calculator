#include <iostream>
#include <limits>
#include <string>
#include "cli/parser.h"
#include "core/Debug.h"

namespace duke::cli {

int lerOpcao12(int padrao) {
    int opcao = padrao;
    std::cout << "Quer o calculo com o mais barato ou com o mais caro? (1/2) | ";
    if (!(std::cin >> opcao) || (opcao != 1 && opcao != 2)) {
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        opcao = padrao;
        wr::p("APP", "Entrada invalida. Usando opcao " + std::to_string(padrao) + ".", "Yellow");
    }
    return opcao;
}

} // namespace duke::cli

