#include <iostream>
#include "cli/utils.h"
#include "core/format.h"
#include "ApplicationCore.h"

namespace duke::cli {

void listarMateriais(const std::vector<MaterialDTO>& base) {
    ApplicationCore core;
    const auto& itens = core.listarMateriais(base);
    std::cout << "\nMateriais cadastrados:\n";
    if (itens.empty()) {
        std::cout << "(vazio)\n";
        return;
    }
    for (size_t i = 0; i < itens.size(); ++i) {
        const auto& m = itens[i];
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

