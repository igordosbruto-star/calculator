#include <cassert>
#include <vector>
#include <string>
#include <sstream>
#include "gui/Navigation.h"
#include "gui/GuiBridge.h"

using namespace duke;

void test_menu_key_widget_calls_core() {
    ApplicationCore core;
    std::vector<MaterialDTO> base{
        {"Madeira", 10.0, 0.1, 1.0, "linear"},
        {"Metal", 20.0, 0.2, 2.0, "linear"}
    };
    auto mats = core::reconstruirMateriais(base);
    gui::GuiBridge bridge(core, base, mats);

    std::vector<std::string> opts{"A", "B"};
    std::vector<char> keys{'a', 'b'};
    gui::MenuKeyWidget menu(opts, keys, [&](int idx){ bridge.selecionarMaterial(idx); });

    menu.onKey('b');
    assert(bridge.ultimaSelecao() == 1);
}

void test_main_menu_widget_filter_and_select() {
    std::vector<std::string> opts{"Clientes", "Vendas", "Produção"};
    std::vector<std::string> tips{"Gerenciar clientes", "Registrar vendas", "Linha de produção"};
    std::vector<bool> req{true, false, false};
    int selected = -1;
    gui::MainMenuWidget menu(opts, tips, req, [&](int idx) { selected = idx; });

    menu.filter("ven");
    std::ostringstream out;
    menu.render(out);
    std::string rendered = out.str();
    assert(rendered.find("Vendas") != std::string::npos);
    assert(rendered.find("Clientes") == std::string::npos);

    menu.onInput(1);
    assert(selected == 1);
}

