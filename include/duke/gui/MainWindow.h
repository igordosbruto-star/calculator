#pragma once

#include <wx/frame.h>
#include <vector>
#include <utility>

class wxPanel;
class wxBoxSizer;
class wxButton;
class wxTextCtrl;
class wxMenuBar;
class wxMenu;

#include "gui/GuiBridge.h"

namespace duke {
namespace gui {

// ==========================================
// Classe: MainWindow
// Descrição: janela principal da aplicação.
// Exemplo de uso:
//   MainWindow w(&bridge, nullptr, nullptr, nullptr);
// ==========================================
class MainWindow : public wxFrame {
public:
    // Construtor: prepara a janela com ponteiros para widgets.
    MainWindow(gui::GuiBridge* bridge,
               wxPanel* centralPanel,
               wxBoxSizer* layout,
               wxButton* selectButton);

    // Destrutor padrão.
    ~MainWindow() override = default;

private:
    gui::GuiBridge* m_bridge;
    wxPanel* m_centralPanel;
    wxBoxSizer* m_layout;
    wxButton* m_selectButton;
    wxTextCtrl* m_searchField;
    wxMenuBar* m_menuBar;
    std::vector<std::pair<wxMenu*, wxString>> m_menus;
};

} // namespace gui
} // namespace duke

