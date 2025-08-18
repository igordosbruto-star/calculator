#include "duke.hpp"

namespace duke {

double calcularValorCorte(const Material& material,
                          double largura,
                          double comprimento) {
    double area = largura * comprimento;
    return area * material.capPorm2();
}

} // namespace duke

