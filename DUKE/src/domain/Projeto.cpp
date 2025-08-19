#include "domain/Projeto.h"

#include <algorithm>
#include <cmath>
#include "custo/EstimadorCusto.h"
#include "domain/MaterialUnitario.h"
#include "domain/Tempo.h"
namespace duke {

// Retorna false se qualquer dimensão for menor ou igual a zero
static bool medidasValidas(const Medidas& m) {
    if (m.largura <= 0 || m.altura <= 0 || m.profundidade <= 0 || m.comprimento <= 0)
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

bool Projeto::adicionarOperacao(const Operacao& op) {
    if (op.tempoPorUnidade <= 0) return false;
    if (op.quantidade <= 0) return false;
    operacoes.push_back(op);
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

double Projeto::tempoTotal() const {
    return Tempo::tempoProjeto(operacoes);
}

// Função auxiliar para arredondar valores
static double arredondar(double valor, int casas) {
    double fator = std::pow(10.0, casas);
    return std::round(valor * fator) / fator;
}

// Calcula custos detalhados do projeto utilizando EstimadorCusto
ResumoCustoProjeto Projeto::calcularCustos(const CustoParams& params) const {
    EstimadorCusto est;
    ResumoCustoProjeto resumo;
    double subtotal = 0.0;

    // Materiais
    for (const auto& m : materiais) {
        ItemReq req{m.idMaterial, "unitario", m.quantidade, m.medidas};
        MaterialUnitario mat(m.custoUnitario);
        double custo = est.custoMaterial(req, mat);
        custo *= (1.0 + params.perdaPadrao);
        resumo.itens.push_back({m.idMaterial, custo});
        subtotal += custo;
    }

    // Cortes
    for (const auto& c : cortes) {
        Medidas md{c.largura, 0.0, 0.0, c.comprimento};
        ItemReq req{c.idMaterial, "unitario", c.quantidade, md};
        MaterialUnitario mat(c.custoUnitario);
        double custo = est.custoMaterial(req, mat);
        custo *= (1.0 + params.perdaPadrao);
        resumo.itens.push_back({c.idMaterial, custo});
        subtotal += custo;
    }

    double maoDeObra = tempoTotal() * params.fatorMaoObra;
    double parcial = subtotal + maoDeObra;
    double valorOverhead = parcial * params.overhead;
    parcial += valorOverhead;
    double total = parcial * (1.0 + params.markup);
    resumo.total = arredondar(total, params.casasDecimais);

    return resumo;
}

} // namespace duke
