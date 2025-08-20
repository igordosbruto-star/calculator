#include "gui/MainWindow.h"

#include <wx/wx.h>
#include <vector>
#include <utility>

namespace duke {
namespace gui {

wxBEGIN_EVENT_TABLE(MainWindow, wxFrame)
    EVT_TEXT(wxID_ANY, MainWindow::OnSearchFieldText)
    EVT_BUTTON(wxID_ANY, MainWindow::OnSelectButton)
wxEND_EVENT_TABLE()

// Construtor: inicializa widgets e conecta eventos.
MainWindow::MainWindow(gui::GuiBridge* bridge,
                       wxPanel* centralPanel,
                       wxBoxSizer* layout,
                       wxButton* selectButton)
    : wxFrame(nullptr, wxID_ANY, "Duke Calculator"),
      m_bridge(bridge),
      m_centralPanel(centralPanel),
      m_layout(layout),
      m_selectButton(selectButton),
      m_searchField(nullptr),
      m_menuBar(nullptr) {
    // cria sizer vertical se não informado
    if (!m_layout) {
        m_layout = new wxBoxSizer(wxVERTICAL);
    }
    SetSizer(m_layout);

    // cria painel central se não informado
    if (!m_centralPanel) {
        m_centralPanel = new wxPanel(this);
    }
    m_layout->Add(m_centralPanel, 1, wxEXPAND | wxALL, 5);

    // sizer interno do painel
    wxBoxSizer* panelSizer = new wxBoxSizer(wxVERTICAL);
    m_centralPanel->SetSizer(panelSizer);

    // campo de busca com tooltip e destaque
    m_searchField = new wxTextCtrl(m_centralPanel, wxID_ANY);
    m_searchField->SetHint("Buscar...");
    m_searchField->SetToolTip("Digite para filtrar opções");
    m_searchField->SetBackgroundColour(*wxRED);
    panelSizer->Add(m_searchField, 0, wxEXPAND | wxALL, 5);

    // cria botão de seleção se não informado
    if (!m_selectButton) {
        m_selectButton = new wxButton(m_centralPanel, wxID_ANY, "Selecionar");
    }
    panelSizer->Add(m_selectButton, 0, wxEXPAND | wxALL, 5);

    // menu principal com itens
    m_menuBar = new wxMenuBar();
    SetMenuBar(m_menuBar);
    const std::vector<std::pair<wxString, wxString>> menus{
        {"Clientes", "Gerenciar clientes"},
        {"Vendas", "Registrar vendas"},
        {"Produção", "Controle de produção"},
        {"Administração", "Configurações administrativas"},
        {"Relatórios", "Visualizar relatórios"},
        {"Configurações", "Preferências do sistema"}};
    for (const auto& m : menus) {
        wxMenu* menu = new wxMenu();
        m_menuBar->Append(menu, m.first);
        m_menus.push_back({menu, m.first});
    }
}

void MainWindow::OnSearchFieldText(wxCommandEvent& evt) {
    wxString txt = evt.GetString();
    if (txt.IsEmpty()) {
        m_searchField->SetBackgroundColour(*wxRED);
    } else {
        m_searchField->SetBackgroundColour(wxNullColour);
    }
    m_searchField->Refresh();
    for (auto& pair : m_menus) {
        int pos = m_menuBar->FindMenu(pair.second);
        if (pos != wxNOT_FOUND) {
            bool vis = pair.second.Lower().Find(txt.Lower()) != wxNOT_FOUND;
            m_menuBar->EnableTop(pos, vis);
        }
    }
}

void MainWindow::OnSelectButton(wxCommandEvent& evt) {
    (void)evt;
    if (m_bridge) {
        m_bridge->selecionarMaterial(0);
    }
}

} // namespace gui
} // namespace duke

