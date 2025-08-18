#include <iostream>
#include "cli/utils.h"
#include "core/format.h"

namespace duke::cli {

void listarMateriais(const std::vector<MaterialDTO>& base) {
    std::cout << "\nMateriais cadastrados:\n";
    if (base.empty()) {
        std::cout << "(vazio)\n";
        return;
    }
    for (size_t i = 0; i < base.size(); ++i) {
        const auto& m = base[i];
        std::cout << i + 1 << ") " << m.nome << " [" << m.tipo << "]"
                  << " | " << UN_MONE << m.valor
                  << " | " << m.largura << " x " << m.comprimento << UN_AREA
                  << "\n";
    }
}

void salvarReconstruir(std::vector<MaterialDTO>& base, std::vector<Material>& mats) {
    mats = core::reconstruirMateriais(base);
    ::Persist::saveJSON("materiais.json", base, 1);
}

} // namespace duke::cli

