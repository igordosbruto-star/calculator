#pragma once

#include "domain/MaterialBase.h"
namespace duke {

// Material vendido por unidade
class MaterialUnitario : public MaterialBase {
    double precoUnitario = 0.0; // preco por unidade

public:
    explicit MaterialUnitario(double preco);

    std::string tipo() const override;
    double custo(double qtd, const Medidas& m) const override;
};
} // namespace duke
