#include "duke/duke.hpp"
#include <cassert>

// Testa interface pública simplificada
void test_duke_api() {
    CliOptions opt;
    opt.showHelp = true;
    int res = processarComando(opt);
    assert(res == 0);
}

