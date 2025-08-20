#include "comparison.h"
#include <algorithm>
#include <cctype>
#include <sstream>
#include <stdexcept>
#include <unordered_set>
#include "core.h"

namespace duke::comparison {

std::vector<Material> selecionarMateriais(const std::vector<int>& ids,
                                          const std::vector<Material>& mats) {
    if (ids.size() < 2) {
        throw std::invalid_argument("Selecione ao menos dois materiais");
    }
    std::vector<Material> sel;
    sel.reserve(ids.size());
    for (int i : ids) {
        if (i < 0 || static_cast<size_t>(i) >= mats.size()) {
            throw std::out_of_range("Indice invalido");
        }
        sel.push_back(mats[static_cast<size_t>(i)]);
    }
    return sel;
}

Selecionados selecionarMateriais(const std::string& ids,
                                 const std::vector<Material>& mats) {
    std::istringstream iss(ids);
    std::vector<int> vecIds;
    std::unordered_set<int> vistos;
    std::string token;
    while (iss >> token) {
        if (token.empty() ||
            !std::all_of(token.begin(), token.end(),
                         [](unsigned char c) { return std::isdigit(c); })) {
            throw std::invalid_argument("Token nao numerico");
        }
        int idx = std::stoi(token) - 1;
        if (!vistos.insert(idx).second) {
            throw std::invalid_argument("Indice duplicado");
        }
        vecIds.push_back(idx);
    }
    Selecionados sel;
    sel.materiais = selecionarMateriais(vecIds, mats);
    sel.indices = std::move(vecIds);
    return sel;
}

std::vector<MaterialComparado> compararMateriais(
    const std::vector<Material>& matsSelecionados) {
    if (matsSelecionados.size() < 2) {
        throw std::invalid_argument("Selecione ao menos dois materiais");
    }
    auto ext = core::extremosPorM2(matsSelecionados);
    std::vector<MaterialComparado> res;
    res.reserve(matsSelecionados.size());
    for (const auto& m : matsSelecionados) {
        MaterialComparado mc;
        mc.nome = m.getNome();
        mc.porm2 = m.getPorm2();
        if (m.getNome() == ext.menor.nome) mc.menor = true;
        if (m.getNome() == ext.maior.nome) mc.maior = true;
        res.push_back(mc);
    }
    return res;
}

} // namespace duke::comparison

