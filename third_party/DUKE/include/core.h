#pragma once

#include <vector>
#include <string>
#include "Material.h"
#include "core/persist.h"
namespace duke {

namespace core {
    // Base de comparação com nome e valor
    // Exemplo:
    //   Base b{"Madeira", 10.0};
    struct Base {
        std::string nome; // nome do material
        double valor = 0.0; // valor associado
    };

    // Contém menor e maior valores na comparação
    // Exemplo:
    //   Como c{ {"A",1.0}, {"B",2.0} };
    struct Como {
        Base menor; // material com menor valor
        Base maior; // material com maior valor
    };

    // Retorna materiais reconstruídos a partir de DTOs
    // Exemplo:
    //   std::vector<Material> m = core::reconstruirMateriais(dtos);
    std::vector<Material> reconstruirMateriais(const std::vector<MaterialDTO>& v);

    // Calcula materiais com menor e maior preço por m2
    // Lança `std::invalid_argument` se `mats` estiver vazio
    // Exemplo:
    //   Como c = core::extremosPorM2(mats);
    Como extremosPorM2(const std::vector<Material>& mats);
}

} // namespace duke
