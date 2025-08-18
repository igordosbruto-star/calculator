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

    // testa --projeto com caminho
    const char* a3[] = {"app", "--projeto", "proj.json"};
    CliOptions o3 = parseArgs(3, const_cast<char**>(a3));
    assert(o3.projeto == "proj.json");

    // testa comandos
    const char* a4[] = {"app", "criar"};
    CliOptions o4 = parseArgs(2, const_cast<char**>(a4));
    assert(o4.comando == Comando::Criar);

    const char* a5[] = {"app", "listar"};
    CliOptions o5 = parseArgs(2, const_cast<char**>(a5));
    assert(o5.comando == Comando::Listar);

    const char* a6[] = {"app", "comparar"};
    CliOptions o6 = parseArgs(2, const_cast<char**>(a6));
    assert(o6.comando == Comando::Comparar);

    // testa flags extras
    const char* a7[] = {"app", "--tipo", "linear"};
    CliOptions o7 = parseArgs(3, const_cast<char**>(a7));
    assert(o7.tipo == "linear");

    const char* a8[] = {"app", "--ordem=preco:asc"};
    CliOptions o8 = parseArgs(2, const_cast<char**>(a8));
    assert(o8.ordem == "preco:asc");

    const char* a9[] = {"app", "--ids", "1,3,5"};
    CliOptions o9 = parseArgs(3, const_cast<char**>(a9));
    assert(o9.ids.size() == 3);
    assert(o9.ids[0] == 1 && o9.ids[1] == 3 && o9.ids[2] == 5);
}
