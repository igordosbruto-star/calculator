#pragma once

#include "domain/MaterialBase.h"
namespace calculadora {

// Material vendido por metro cúbico
class MaterialCubico : public MaterialBase {
    double precoM3 = 0.0; // preco por metro cubico

public:
    explicit MaterialCubico(double preco);

    std::string tipo() const override;
    double custo(double qtd, const Medidas& m) const override;
};
} // namespace calculadora
