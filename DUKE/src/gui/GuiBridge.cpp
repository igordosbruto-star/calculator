#include "gui/GuiBridge.h"

namespace duke {
namespace gui {

GuiBridge::GuiBridge(ApplicationCore& core,
                     const std::vector<MaterialDTO>& base,
                     const std::vector<Material>& mats)
    : m_core(core), m_base(base), m_mats(mats) {}

void GuiBridge::selecionarMaterial(int idx) {
    // Chama listarMateriais apenas para demonstrar conexão.
    m_core.listarMateriais(m_base);
    m_last = idx;
}

} // namespace gui
} // namespace duke

