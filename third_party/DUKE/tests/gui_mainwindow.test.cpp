#include <QApplication>
#include <QPushButton>
#include <QtTest/QTest>
#include <QMenuBar>
#include <QLineEdit>
#include <vector>
#include <cassert>
#include "gui/MainWindow.h"
#include "gui/GuiBridge.h"

using namespace duke;

int main(int argc, char** argv) {
    setenv("QT_QPA_PLATFORM", "offscreen", 1);
    QApplication app(argc, argv);

    ApplicationCore core;
    std::vector<MaterialDTO> base{{"Madeira", 10.0, 0.1, 1.0, "linear"}};
    auto mats = core::reconstruirMateriais(base);

    gui::GuiBridge bridge(core, base, mats);
    gui::MainWindow window(&bridge, nullptr, nullptr, nullptr);
    window.show();

    QPushButton* button = window.findChild<QPushButton*>();
    QTest::mouseClick(button, Qt::LeftButton);

    assert(bridge.ultimaSelecao() == 0);

    QMenuBar* bar = window.menuBar();
    auto actions = bar->actions();
    assert(actions.size() == 6);
    assert(actions[1]->toolTip() == "Registrar vendas");

    QLineEdit* search = window.findChild<QLineEdit*>("searchField");
    assert(search->toolTip() == "Digite para filtrar opções");
    assert(search->styleSheet().contains("red"));

    QTest::keyClicks(search, "Ven");
    int visible = 0;
    for (auto* act : actions) {
        if (act->isVisible()) visible++;
    }
    assert(visible == 1);
    assert(actions[1]->isVisible());
    return 0;
}
