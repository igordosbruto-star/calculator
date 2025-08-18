#include "domain/MaterialFactory.h"
#include "domain/MaterialUnitario.h"
#include "domain/MaterialLinear.h"
#include "domain/MaterialCubico.h"
#include <stdexcept>
namespace calculadora {

// Cria instância concreta conforme o tipo informado
// Exemplo: fromDTO({"Item",10,0,0,"unitario"}) -> MaterialUnitario
std::unique_ptr<MaterialBase> MaterialFactory::fromDTO(const MaterialDTO& dto) {
    if (dto.tipo == "unitario") {
        return std::make_unique<MaterialUnitario>(dto.valor);
    }
    if (dto.tipo == "linear") {
        return std::make_unique<MaterialLinear>(dto.valor, 0.0);
    }
    if (dto.tipo == "cubico") {
        return std::make_unique<MaterialCubico>(dto.valor);
    }
    throw std::invalid_argument("tipo desconhecido: " + dto.tipo);
}
} // namespace calculadora
