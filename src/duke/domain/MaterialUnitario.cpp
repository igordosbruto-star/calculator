#include "domain/MaterialUnitario.h"
namespace duke {

// Construtor com preco por unidade
// Exemplo: MaterialUnitario mu(5.0);
MaterialUnitario::MaterialUnitario(double preco)
    : precoUnitario(preco) {}

// Retorna o identificador do tipo
// Exemplo: mu.tipo() => "unitario"
std::string MaterialUnitario::tipo() const { return "unitario"; }

// Calcula o custo total
// Exemplo: precoUnitario=5.0, qtd=3 => custo=15.0
double MaterialUnitario::custo(double qtd, const Medidas&) const {
    return precoUnitario * qtd;
}
} // namespace duke
