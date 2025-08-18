#pragma once

#include <string>

// Estrutura com medidas de um item
struct Medidas {
    double largura = 0.0;       // em metros
    double altura = 0.0;        // em metros
    double profundidade = 0.0;  // em metros
    double comprimento = 0.0;   // em metros (usado para materiais lineares)
};

// Classe base para diferentes tipos de materiais
class MaterialBase {
public:
    virtual ~MaterialBase() = default;

    // Retorna o tipo do material
    virtual std::string tipo() const = 0;

    // Calcula o custo total dado uma quantidade e medidas
    virtual double custo(double qtd, const Medidas& m) const = 0;
};
