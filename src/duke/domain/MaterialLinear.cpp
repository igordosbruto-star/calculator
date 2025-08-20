#include "domain/MaterialLinear.h"
namespace duke {

// Construtor com preco por metro e percentual de perda
// Exemplo: MaterialLinear ml(10.0, 0.1);
MaterialLinear::MaterialLinear(double preco, double perdaPct)
    : precoM(preco), perda(perdaPct) {}

// Retorna o identificador do tipo
// Exemplo: ml.tipo() => "linear"
std::string MaterialLinear::tipo() const { return "linear"; }

// Calcula o custo total considerando perda
// Exemplo: precoM=10, perda=0.1, metros=2, qtd=4 => 10*2*4*1.1=88
double MaterialLinear::custo(double qtd, const Medidas& m) const {
    double metros = m.comprimento;
    return precoM * metros * qtd * (1.0 + perda);
}
} // namespace duke
