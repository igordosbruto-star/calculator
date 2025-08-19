#include <QApplication>
#include <QPushButton>
#include <QtTest/QTest>
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
    return 0;
}
