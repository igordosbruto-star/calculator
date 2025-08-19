#include "gui/GuiBridge.h"
#include "core/Debug.h"
#include <string>

namespace duke {
namespace gui {

GuiBridge::GuiBridge(ApplicationCore& core,
                     const std::vector<MaterialDTO>& base,
                     const std::vector<Material>& mats,
                     QObject* parent)
    : QObject{parent}, m_core(core), m_base(base), m_mats(mats), m_last{-1} {}

void GuiBridge::selecionarMaterial(int idx) {
    wr::p("GUI", "Selecionando material " + std::to_string(idx), "Blue");
    // Chama listarMateriais apenas para demonstrar conexão.
    m_core.listarMateriais(m_base);
    m_last = idx;
}

} // namespace gui
} // namespace duke

