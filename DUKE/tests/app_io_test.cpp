#include <cassert>
#include <sstream>
#include <string>
#include "nlohmann/json.hpp"

#define private public
#include "cli/App.h"
#undef private

using namespace duke;

// Testa se importarCSV descarta o resto da linha corretamente
void test_importarCSV_ignore() {
    App app;
    std::istringstream in("n\nproximo\n");
    auto old = std::cin.rdbuf(in.rdbuf());
    app.importarCSV();
    std::string linha;
    std::getline(std::cin, linha);
    std::cin.rdbuf(old);
    assert(linha == "proximo");
}

// Testa se exportar descarta o resto da linha corretamente
void test_exportar_ignore() {
    App app;
    std::istringstream in("n\noutra\n");
    auto old = std::cin.rdbuf(in.rdbuf());
    app.exportar();
    std::string linha;
    std::getline(std::cin, linha);
    std::cin.rdbuf(old);
    assert(linha == "outra");
}
