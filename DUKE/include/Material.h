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

    const std::string& capNome() const noexcept;
    double capValor() const noexcept;
    double capArea()  const noexcept;
    double capLarg()  const noexcept;
    double capComp()  const noexcept;
    double capPorm2() const noexcept;

    void aplLarg(double l);
    void aplComp(double c);
    void aplValor(double v);

    void mostrar() const;
};

} // namespace duke
