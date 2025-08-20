// ==========================================
// Arquivo: main_qt.cpp
// Descrição: Ponto de entrada para interface Qt
// ==========================================

#include <QApplication>
#include "gui/MainWindow.h"

#ifndef UNIT_TEST
int main(int argc, char* argv[]) {
    QApplication app(argc, argv);
    MainWindow w;
    w.show();
    return app.exec();
}
#endif // UNIT_TEST

