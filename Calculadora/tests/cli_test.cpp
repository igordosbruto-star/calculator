#include "cli.h"
#include <cassert>

// Testa o parsing de argumentos basicos
void test_cli() {
    // testa --help
    const char* a1[] = {"app", "--help"};
    CliOptions o1 = parseArgs(2, const_cast<char**>(a1));
    assert(o1.showHelp);
    assert(!o1.autoMode);

    // testa --auto
    const char* a2[] = {"app", "--auto"};
    CliOptions o2 = parseArgs(2, const_cast<char**>(a2));
    assert(o2.autoMode);
    assert(!o2.showHelp);
}
