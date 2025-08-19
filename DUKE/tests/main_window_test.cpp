#include <cassert>
#include <vector>
#include <cstdlib>
#include <QApplication>
#include <QPushButton>
#include <QVBoxLayout>
#include "gui/MainWindow.h"
#include "gui/GuiBridge.h"

using namespace duke;

// Testa se o clique no botão chama GuiBridge::selecionarMaterial.
void test_main_window_button_calls_bridge() {
    setenv("QT_QPA_PLATFORM", "offscreen", 1);
    int argc = 0;
    char** argv = nullptr;
    QApplication app(argc, argv);

    ApplicationCore core;
    std::vector<MaterialDTO> base{
        {"Madeira", 10.0, 0.1, 1.0, "linear"}
    };
    auto mats = core::reconstruirMateriais(base);
    gui::GuiBridge bridge(core, base, mats);

    auto central = new QWidget;
    auto layout = new QVBoxLayout(central);
    auto button = new QPushButton("Selecionar");

    gui::MainWindow window(&bridge, central, layout, button);
    button->click();

    assert(bridge.ultimaSelecao() == 0);
}
