#pragma once

#include <vector>
#include "ApplicationCore.h"
#include "Material.h"
#include "core.h"

namespace duke {
namespace gui {

// ==========================================
// Classe: GuiBridge
// Descrição: conecta eventos do GUI aos métodos
//            de ApplicationCore.
// Exemplo de uso:
//   GuiBridge b(core, base, mats);
//   b.selecionarMaterial(0);
// ==========================================
class GuiBridge {
public:
    GuiBridge(ApplicationCore& core,
              const std::vector<MaterialDTO>& base,
              const std::vector<Material>& mats);

    void selecionarMaterial(int idx);

    int ultimaSelecao() const { return m_last; }

private:
    ApplicationCore& m_core;
    const std::vector<MaterialDTO>& m_base;
    const std::vector<Material>& m_mats;
    int m_last;
};

} // namespace gui
} // namespace duke

