#include "core.h"
#include <algorithm>
#include <stdexcept>
namespace duke {

namespace core {
    std::vector<Material> reconstruirMateriais(const std::vector<MaterialDTO>& v) {
        std::vector<Material> mats;
        mats.reserve(v.size());
        for (const auto& d : v) {
            mats.emplace_back(d.nome, d.valor, d.largura, d.comprimento);
        }
        return mats;
    }

    Como extremosPorM2(const std::vector<Material>& mats) {
        if (mats.empty()) {
            // Vetor vazio não possui extremos
            throw std::invalid_argument("Lista de materiais vazia");
        }
        auto cmp = [](const Material& a, const Material& b){ return a.getPorm2() < b.getPorm2(); };
        auto [min_it, max_it] = std::minmax_element(mats.begin(), mats.end(), cmp);
        return {{min_it->getNome(), min_it->getPorm2()}, {max_it->getNome(), max_it->getPorm2()}};
    }
}

} // namespace duke
