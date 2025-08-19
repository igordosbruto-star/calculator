#include "gui/MainWindow.h"

#include <QWidget>
#include <QVBoxLayout>
#include <QPushButton>
#include <QObject>

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
      m_selectButton(selectButton) {
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
    m_layout->addWidget(m_selectButton);
    // conecta clique do botão à ponte de seleção
    QObject::connect(m_selectButton, &QPushButton::clicked,
                     [this]() { if (m_bridge) m_bridge->selecionarMaterial(0); });
}

} // namespace gui
} // namespace duke

