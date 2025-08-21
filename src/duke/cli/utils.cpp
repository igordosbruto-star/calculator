#include <iostream>
#include "cli/utils.h"
#include "core/format.h"
#include "ApplicationCore.h"
#include "ui/Menu.h"

namespace duke::cli {

size_t readMaterialIndex(const std::vector<MaterialDTO>& base, const std::string& prompt) {
    size_t idx = 0;
    while (true) {
        int input = ui::readInt(prompt);
        if (input >= 1 && static_cast<size_t>(input) <= base.size()) {
            idx = static_cast<size_t>(input - 1);
            break;
        }
        std::cout << "Indice invalido.\n";
    }
    return idx;
}

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

