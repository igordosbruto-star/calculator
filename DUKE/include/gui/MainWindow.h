#pragma once

#include <QMainWindow>
#include <vector>

QT_BEGIN_NAMESPACE
class QWidget;
class QVBoxLayout;
class QPushButton;
class QLineEdit;
class QMenuBar;
class QAction;
QT_END_NAMESPACE

#include "gui/GuiBridge.h"

namespace duke {
namespace gui {

// ==========================================
// Classe: MainWindow
// Descrição: janela principal da aplicação.
// Exemplo de uso:
//   MainWindow w(&bridge, nullptr, nullptr, nullptr);
// ==========================================
class MainWindow : public QMainWindow {
public:
    // Construtor: prepara a janela com ponteiros para widgets.
    MainWindow(gui::GuiBridge* bridge,
               QWidget* centralWidget,
               QVBoxLayout* layout,
               QPushButton* selectButton);

    // Destrutor padrão.
    ~MainWindow() override = default;

private:
    gui::GuiBridge* m_bridge;
    QWidget* m_centralWidget;
    QVBoxLayout* m_layout;
    QPushButton* m_selectButton;
    QLineEdit* m_searchField;
    QMenuBar* m_menuBar;
    std::vector<QAction*> m_actions;
};

} // namespace gui
} // namespace duke

