#pragma once

#include <string>

class Corte {
private:
    std::string nome;
    double largura     = 0.0; // em metros
    double comprimento = 0.0; // em metros
    double porm2       = 0.0; // preço por m² aplicado a este corte
    double area        = 0.0; // largura * comprimento
    double valor       = 0.0; // area * porm2

public:
    Corte(const std::string& n, double l, double c, double precoPorM2);

    double capArea() const noexcept;
    double capValor() const noexcept;

    void imprimir() const;
};

