#include "domain/MaterialCubico.h"

// Construtor com preco por metro cubico
// Exemplo: MaterialCubico mc(100.0);
MaterialCubico::MaterialCubico(double preco)
    : precoM3(preco) {}

// Retorna o identificador do tipo
// Exemplo: mc.tipo() => "cubico"
std::string MaterialCubico::tipo() const { return "cubico"; }

// Calcula o custo total a partir do volume
// Exemplo: precoM3=100, L=2, A=0.5, P=1, qtd=3 => 100*1*3=300
double MaterialCubico::custo(double qtd, const Medidas& m) const {
    double volume = m.largura * m.altura * m.profundidade;
    return precoM3 * volume * qtd;
}
