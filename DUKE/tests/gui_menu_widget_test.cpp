#include <cassert>
#include <vector>
#include <string>
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

