#include "Material.h"
#include "core/format.h"
#include <iostream>
namespace calculadora {

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

const std::string& Material::capNome() const noexcept { return nome; }
double Material::capValor() const noexcept { return valor; }
double Material::capArea()  const noexcept { return area; }
double Material::capLarg()  const noexcept { return largura; }
double Material::capComp()  const noexcept { return comprimento; }
double Material::capPorm2() const noexcept { return porm2; }

void Material::aplLarg(double l) { largura = l; iniciar(); }
void Material::aplComp(double c) { comprimento = c; iniciar(); }
void Material::aplValor(double v) { valor = v; iniciar(); }

void Material::mostrar() const {
    std::cout << "Material      : " << capNome() << "\n"
              << "Area          : " << capArea() << UN_AREA << "\n"
              << "Valor Total   : " << UN_MONE << capValor() << "\n"
              << "Valor por m2  : " << UN_MONE << capPorm2() << "\n\n";
}

} // namespace calculadora
