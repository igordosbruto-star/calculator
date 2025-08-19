#include "ApplicationCore.h"
#include <sstream>
#include <stdexcept>
#include "core/Debug.h"

namespace duke {

bool ApplicationCore::carregarJSON(std::vector<MaterialDTO>& base, std::vector<Material>& mats) {
    int schemaVersion = 0;
    if (!::Persist::loadJSON("materiais.json", base, &schemaVersion) || base.empty()) {
        wr::p("DATA", "Base nao encontrada. Criando materiais padrao...", "Yellow");
        base = {
            {"Pinus 20cm", 17.00, 0.20, 3.00, "linear"},
            {"MDF 15mm", 180.00, 1.85, 2.75, "linear"}
        };
        if (::Persist::saveJSON("materiais.json", base, 1)) {
            wr::p("DATA", "materiais.json criado.", "Green");
        } else {
            wr::p("DATA", "Falha ao criar materiais.json", "Red");
        }
    } else {
        std::ostringstream oss;
        oss << "materiais.json carregado (versao " << schemaVersion << ")";
        wr::p("DATA", oss.str(), "Green");
    }

    mats = core::reconstruirMateriais(base);
    if (mats.size() < 2) {
        wr::p("ERRO", "Precisam existir pelo menos 2 materiais para comparar.", "Red");
        return false;
    }
    return true;
}

std::vector<MaterialDTO> ApplicationCore::listarMateriais(const std::vector<MaterialDTO>& base) const {
    return base;
}

std::vector<ApplicationCore::MaterialComparado>
ApplicationCore::compararMateriais(const std::vector<Material>& mats,
                                   const std::vector<int>& ids) const {
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
    auto ext = core::extremosPorM2(sel);
    std::vector<MaterialComparado> res;
    res.reserve(ids.size());
    for (int i : ids) {
        const auto& m = mats[static_cast<size_t>(i)];
        MaterialComparado mc;
        mc.nome = m.getNome();
        mc.porm2 = m.getPorm2();
        if (m.getNome() == ext.menor.nome) mc.menor = true;
        if (m.getNome() == ext.maior.nome) mc.maior = true;
        res.push_back(mc);
    }
    return res;
}

} // namespace duke

