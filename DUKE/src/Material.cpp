#include "Material.h"
#include "core/format.h"
#include <iostream>
namespace duke {

void Material::iniciar() noexcept {
    area = largura * comprimento;
    porm2 = (area > 0.0) ? (valor / area) : 0.0;
}

Material::Material(const std::string& n)
    : nome(n) {
    iniciar();
}

Material::Material(const std::string& n, double v, double l, double c)
    : nome(n), valor(v), largura(l), comprimento(c) {
    iniciar();
}

const std::string& Material::getNome() const noexcept { return nome; }
double Material::getValor() const noexcept { return valor; }
double Material::getArea()  const noexcept { return area; }
double Material::getLarg()  const noexcept { return largura; }
double Material::getComp()  const noexcept { return comprimento; }
double Material::getPorm2() const noexcept { return porm2; }

void Material::setLarg(double l) { largura = l; iniciar(); }
void Material::setComp(double c) { comprimento = c; iniciar(); }
void Material::setValor(double v) { valor = v; iniciar(); }

void Material::mostrar() const {
    std::cout << "Material      : " << getNome() << "\n"
              << "Area          : " << getArea() << UN_AREA << "\n"
              << "Valor Total   : " << UN_MONE << getValor() << "\n"
              << "Valor por m2  : " << UN_MONE << getPorm2() << "\n\n";
}

} // namespace duke
