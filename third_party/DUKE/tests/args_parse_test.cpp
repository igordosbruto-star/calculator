#include <cassert>
#include <sstream>
#include <string>
#include <iostream>
#include "cli/args.h"

using namespace duke;

// Verifica captura de argumentos desconhecidos
void test_parseArgs_unknown() {
    char arg0[] = "app";
    char arg1[] = "--foo";
    char* argv[] = {arg0, arg1};
    std::ostringstream out;
    auto old = std::cout.rdbuf(out.rdbuf());
    CliOptions opt = parseArgs(2, argv);
    std::cout.rdbuf(old);
    assert(!opt.ok);
    assert(opt.naoMapeados.size() == 1);
    assert(opt.naoMapeados[0] == "--foo");
    assert(out.str().find("Argumento desconhecido: --foo") != std::string::npos);
}
