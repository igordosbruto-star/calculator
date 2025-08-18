#include "custo/EstimadorCusto.h"

#include <cmath>

// Calcula o custo de um material específico
// Exemplo: ItemReq req{...}; MaterialUnitario m(5.0);
// EstimadorCusto est; est.custoMaterial(req, m);
double EstimadorCusto::custoMaterial(const ItemReq& req, const MaterialBase& m) const {
    return m.custo(req.qtd, req.medidas);
}

// Função auxiliar para arredondar
static double arredondar(double valor, int casas) {
    double fator = std::pow(10.0, casas);
    return std::round(valor * fator) / fator;
}

// Calcula o custo total do projeto
// Exemplo: EstimadorCusto est; est.custoProjeto(prj, cfg);
double EstimadorCusto::custoProjeto(const Projeto& prj, const CustoParams& cfg) const {
    double subtotal = 0.0;
    for (const auto& item : prj.materiais) {
        if (item.material != nullptr) {
            subtotal += custoMaterial(item.req, *item.material);
        }
    }
    subtotal *= (1.0 + cfg.perdaPadrao);
    subtotal *= (1.0 + cfg.fatorMaoObra);
    subtotal *= (1.0 + cfg.markup);
    return arredondar(subtotal, cfg.casasDecimais);
}

