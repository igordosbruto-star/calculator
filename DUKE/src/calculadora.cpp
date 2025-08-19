#include "duke.hpp"

namespace duke {

double calcularValorCorte(const Material& material,
                          double largura,
                          double comprimento) {
    double area = largura * comprimento;
    return area * material.getPorm2();
}

} // namespace duke

