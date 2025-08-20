#include <cassert>
#include <sstream>
#include <vector>
#include <iostream>
#include "cli/parser.h"
#include "cli/commands.h"

using namespace duke;

void test_lerOpcao12() {
    std::istringstream in("3\n");
    auto old = std::cin.rdbuf(in.rdbuf());
    int v = cli::lerOpcao12(2);
    std::cin.rdbuf(old);
    assert(v == 2);
}

void test_adicionarMaterial() {
    std::vector<MaterialDTO> base;
    std::vector<Material> mats;
    std::istringstream in("\nMadeira\nlinear\n10\n2\n3\n");
    auto old = std::cin.rdbuf(in.rdbuf());
    cli::adicionarMaterial(base, mats);
    std::cin.rdbuf(old);
    assert(base.size() == 1);
    assert(mats.size() == 1);
    assert(base[0].nome == "Madeira");
}

