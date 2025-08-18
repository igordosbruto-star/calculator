#pragma once

#include <memory>
#include "domain/MaterialBase.h"
#include "core/persist.h"
namespace calculadora {

// Factory para criar materiais a partir de um MaterialDTO
class MaterialFactory {
public:
    // Instancia o material concreto baseado no campo tipo do DTO
    // Exemplo:
    //   MaterialDTO d{"Madeira", 5.0, 0, 0, "unitario"};
    //   auto mat = MaterialFactory::fromDTO(d);
    static std::unique_ptr<MaterialBase> fromDTO(const MaterialDTO& dto);
};
} // namespace calculadora
