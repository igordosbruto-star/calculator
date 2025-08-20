#include "gui/MainWindow.h"

#include <QWidget>
#include <QVBoxLayout>
#include <QPushButton>
#include <QObject>
#include <QLineEdit>
#include <QMenuBar>
#include <QAction>
#include <QMenu>
#include <vector>
#include <utility>

namespace duke {
namespace gui {

// Construtor: inicializa widgets e conecta eventos.
MainWindow::MainWindow(gui::GuiBridge* bridge,
                       QWidget* centralWidget,
                       QVBoxLayout* layout,
                       QPushButton* selectButton)
    : QMainWindow(nullptr),
      m_bridge(bridge),
      m_centralWidget(centralWidget),
      m_layout(layout),
      m_selectButton(selectButton),
      m_searchField(nullptr),
      m_menuBar(nullptr) {
    // cria widget central se não informado
    if (!m_centralWidget) {
        m_centralWidget = new QWidget(this);
    }
    // cria layout vertical se não informado
    if (!m_layout) {
        m_layout = new QVBoxLayout(m_centralWidget);
    }
    // cria botão de seleção se não informado
    if (!m_selectButton) {
        m_selectButton = new QPushButton("Selecionar", m_centralWidget);
    }
    // associa hierarquia de widgets
    setCentralWidget(m_centralWidget);
    // campo de busca com tooltip e destaque
    m_searchField = new QLineEdit(m_centralWidget);
    m_searchField->setObjectName("searchField");
    m_searchField->setPlaceholderText("Buscar...");
    m_searchField->setToolTip("Digite para filtrar opções");
    m_searchField->setStyleSheet("border: 2px solid red");
    m_layout->addWidget(m_searchField);

    // menu principal com ações e tooltips
    m_menuBar = new QMenuBar(this);
    setMenuBar(m_menuBar);
    const std::vector<std::pair<QString, QString>> menus{
        {"Clientes", "Gerenciar clientes"},
        {"Vendas", "Registrar vendas"},
        {"Produção", "Controle de produção"},
        {"Administração", "Configurações administrativas"},
        {"Relatórios", "Visualizar relatórios"},
        {"Configurações", "Preferências do sistema"}};
    for (const auto& m : menus) {
        QAction* act = m_menuBar->addAction(m.first);
        act->setToolTip(m.second);
        m_actions.push_back(act);
    }

    // filtro de busca para o menu
    QObject::connect(m_searchField, &QLineEdit::textChanged,
                     [this](const QString& txt) {
                         if (txt.isEmpty()) {
                             m_searchField->setStyleSheet("border: 2px solid red");
                         } else {
                             m_searchField->setStyleSheet("");
                         }
                         for (auto* act : m_actions) {
                             act->setVisible(act->text().contains(txt, Qt::CaseInsensitive));
                         }
                     });

    m_layout->addWidget(m_selectButton);
    // conecta clique do botão à ponte de seleção
    QObject::connect(m_selectButton, &QPushButton::clicked,
                     [this]() { if (m_bridge) m_bridge->selecionarMaterial(0); });
}

} // namespace gui
} // namespace duke

