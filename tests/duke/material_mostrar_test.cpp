#include "duke/Material.h"
#include "core/format.h"
#include <cassert>
#include <sstream>

// Testa Material::mostrar escrevendo em um stream
void test_material_mostrar() {
    Material m{"Madeira", 10.0, 2.0, 3.0};
    std::ostringstream oss;
    m.mostrar(oss);
    std::ostringstream expected;
    expected << "Material      : " << m.getNome() << "\n"
             << "Area          : " << m.getArea() << UN_AREA << "\n"
             << "Valor Total   : " << UN_MONE << m.getValor() << "\n"
             << "Valor por m2  : " << UN_MONE << m.getPorm2() << "\n\n";
    assert(oss.str() == expected.str());
}
