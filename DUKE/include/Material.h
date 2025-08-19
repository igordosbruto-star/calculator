#pragma once

#include <string>
namespace duke {

class Material {
private:
    std::string nome;
    double valor        = 0.0; // valor total da peça/chapas/tábua
    double porm2        = 0.0; // preço por m² (derivado)
    double area         = 0.0; // largura * comprimento (derivado)
    double largura      = 0.0; // em metros
    double comprimento  = 0.0; // em metros

    void iniciar() noexcept;

public:
    Material() = default;
    explicit Material(const std::string& n);
    Material(const std::string& n, double v, double l, double c);

    const std::string& getNome() const noexcept;
    double getValor() const noexcept;
    double getArea()  const noexcept;
    double getLarg()  const noexcept;
    double getComp()  const noexcept;
    double getPorm2() const noexcept;

    void setLarg(double l);
    void setComp(double c);
    void setValor(double v);

    void mostrar() const;
};

} // namespace duke
