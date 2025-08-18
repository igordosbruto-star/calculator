#include "domain/Projeto.h"

#include <algorithm>

// Valida se medidas são estritamente positivas
static bool medidasValidas(const Medidas& m) {
    if (m.largura <= 0 && m.altura <= 0 && m.profundidade <= 0 && m.comprimento <= 0)
        return false;
    if (m.largura < 0 || m.altura < 0 || m.profundidade < 0 || m.comprimento < 0)
        return false;
    return true;
}

bool Projeto::adicionarMaterial(const ProjetoItemMaterial& item) {
    if (item.idMaterial.empty()) return false;
    if (item.quantidade <= 0) return false;
    if (!medidasValidas(item.medidas)) return false;
    materiais.push_back(item);
    return true;
}

bool Projeto::adicionarCorte(const ProjetoItemCorte& item) {
    if (item.idMaterial.empty()) return false;
    if (item.largura <= 0 || item.comprimento <= 0) return false;
    if (item.quantidade <= 0) return false;
    cortes.push_back(item);
    return true;
}

bool Projeto::removerItem(const std::string& idMaterial) {
    auto beforeM = materiais.size();
    materiais.erase(std::remove_if(materiais.begin(), materiais.end(), [&](const auto& m){return m.idMaterial == idMaterial;}), materiais.end());
    auto removed = materiais.size() != beforeM;
    auto beforeC = cortes.size();
    cortes.erase(std::remove_if(cortes.begin(), cortes.end(), [&](const auto& c){return c.idMaterial == idMaterial;}), cortes.end());
    removed = removed || (cortes.size() != beforeC);
    return removed;
}

double Projeto::resumoCusto() const {
    double total = 0.0;
    for (const auto& m : materiais) {
        total += m.quantidade * m.custoUnitario;
    }
    for (const auto& c : cortes) {
        total += c.quantidade * c.custoUnitario;
    }
    return total;
}

