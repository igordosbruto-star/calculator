#include "core.h"
#include <algorithm>

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
        auto cmp = [](const Material& a, const Material& b){ return a.capPorm2() < b.capPorm2(); };
        auto [min_it, max_it] = std::minmax_element(mats.begin(), mats.end(), cmp);
        return {{min_it->capNome(), min_it->capPorm2()}, {max_it->capNome(), max_it->capPorm2()}};
    }
}

