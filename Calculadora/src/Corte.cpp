#include "Corte.h"
#include "core/format.h"
#include <algorithm>
#include <iostream>
namespace calculadora {

Corte::Corte(const std::string& n, double l, double c, double precoPorM2)
    : nome(n),
      largura(std::max(0.0, l)),
      comprimento(std::max(0.0, c)),
      porm2(precoPorM2) {
    area  = largura * comprimento;
    valor = area * porm2;
}

double Corte::capArea() const noexcept { return area; }
double Corte::capValor() const noexcept { return valor; }

void Corte::imprimir() const {
    std::cout << "\nCorte: " << nome << "\n"
              << "Valor por m2 : " << UN_MONE << porm2 << "\n"
              << "Comprimento  : " << comprimento << " m\n"
              << "Largura      : " << largura << " m\n"
              << "Area         : " << area << UN_AREA << "\n"
              << "Valor        : " << UN_MONE << valor << "\n";
}

} // namespace calculadora
