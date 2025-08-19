#include "ui/Menu.h"
#include <cassert>
#include <sstream>

using namespace ui;

// Testa helpers de menu
void test_menu() {
    std::istringstream in1("42\n");
    std::ostringstream out1;
    int i = readInt("? ", in1, out1);
    assert(i == 42);

    std::istringstream in2("x\n7\n");
    std::ostringstream out2;
    int j = readInt("? ", in2, out2);
    assert(j == 7);

    std::istringstream in3("3.14\n");
    std::ostringstream out3;
    double d = readDouble("? ", in3, out3);
    assert(d == 3.14);

    std::istringstream in4("abc\n");
    std::ostringstream out4;
    std::string s = readString("? ", in4, out4);
    assert(s == "abc");

    std::istringstream in5("2\n");
    std::ostringstream out5;
    int opt = promptMenu({"a", "b", "c"}, in5, out5);
    assert(opt == 2);

    std::ostringstream out6;
    renderBreadcrumb({"Principal", "Criar"}, out6);
    assert(out6.str() == "Principal > Criar\n");

    std::istringstream in7("?\nC\n");
    std::ostringstream out7;
    int k = promptMenuKey({"Criar", "Listar"}, {'C','L'}, in7, out7);
    assert(k == 0);
    assert(out7.str().find("Digite a letra") != std::string::npos);
}

