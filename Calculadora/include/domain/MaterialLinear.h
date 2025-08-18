#pragma once

#include "domain/MaterialBase.h"

// Material vendido por metro linear
class MaterialLinear : public MaterialBase {
    double precoM = 0.0; // preco por metro
    double perda = 0.0;  // percentual de perda (0.1 = 10%)

public:
    MaterialLinear(double preco, double perdaPct);

    std::string tipo() const override;
    double custo(double qtd, const Medidas& m) const override;
};
