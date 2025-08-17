// ==========================================
// Arquivo: modulos.h
// Descrição: Declaração das classes e tipos
// ==========================================
#pragma once

// Bibliotecas de Sistema
#include <string>
#include <iostream>
#include <iomanip>

// Bibliotecas Personalizadas
#include "Debug.h"   // logs coloridos

// Constantes globais de unidade
inline constexpr const char* UN_MONE = "R$ ";
inline constexpr const char* UN_AREA = " m²";

// ------------------------------------------------------------
// Classe: Material
// Guarda dados base e calcula valores derivados: área e R$/m².
// ------------------------------------------------------------
class Material {
private:
    std::string nome;
    double valor        = 0.0; // valor total da peça/chapas/tábua
    double porm2        = 0.0; // preço por m² (derivado)
    double area         = 0.0; // largura * comprimento (derivado)
    double largura      = 0.0; // em metros
    double comprimento  = 0.0; // em metros

    // Recalcula os campos derivados com segurança
    void iniciar() noexcept {
        area = largura * comprimento;
        porm2 = (area > 0.0) ? (valor / area) : 0.0;
    }

public:
    Material() = default;

    explicit Material(const std::string& n)
        : nome(n) { iniciar(); }

    Material(const std::string& n, double v, double l, double c)
        : nome(n), valor(v), largura(l), comprimento(c) { iniciar(); }

    // Getters
    const std::string& capNome() const noexcept { return nome; }
    double capValor() const noexcept { return valor; }
    double capArea()  const noexcept { return area; }
    double capLarg()  const noexcept { return largura; }
    double capComp()  const noexcept { return comprimento; }
    double capPorm2() const noexcept { return porm2; }

    // Setters recalculando derivados
    void aplLarg(double l)   { largura = l; iniciar(); }
    void aplComp(double c)   { comprimento = c; iniciar(); }
    void aplValor(double v)  { valor = v; iniciar(); }

    // Impressão (debug)
    void mostrar() const {
        std::cout << "Material      : " << capNome() << "\n"
                  << "Area          : " << capArea() << UN_AREA << "\n"
                  << "Valor Total   : " << UN_MONE << capValor() << "\n"
                  << "Valor por m2  : " << UN_MONE << capPorm2() << "\n\n";
    }
};

// ------------------------------------------------------------
// Classe: Corte
// Representa um pedaço cortado do material.
// ------------------------------------------------------------
class Corte {
private:
    std::string nome;
    double largura     = 0.0; // em metros
    double comprimento = 0.0; // em metros
    double porm2       = 0.0; // preço por m² aplicado a este corte
    double area        = 0.0; // largura * comprimento
    double valor       = 0.0; // area * porm2

public:
    Corte(const std::string& n, double l, double c, double precoPorM2)
        : nome(n), largura(l), comprimento(c), porm2(precoPorM2) {
        area  = largura * comprimento;
        valor = area * porm2;
    }

    void imprimir() const {
        std::cout << "\nCorte: " << nome << "\n"
                  << "Valor por m2 : " << UN_MONE << porm2 << "\n"
                  << "Comprimento  : " << comprimento << " m\n"
                  << "Largura      : " << largura << " m\n"
                  << "Area         : " << area << UN_AREA << "\n"
                  << "Valor        : " << UN_MONE << valor << "\n";
    }
};

// ------------------------------------------------------------
// Tipos auxiliares para comparação de R$/m²
// ------------------------------------------------------------
struct Base { std::string nome; double valor = 0.0; };
struct Como { Base menor, maior; };

// ------------------------------------------------------------
// Classe: App (apenas declaração aqui; implementação em app.cpp)
// ------------------------------------------------------------
class App {
private:
    int dec = 2; // casas decimais para exibição

public:
    double preco = 0.0; // preço/m² escolhido (menor ou maior)
    Como q;             // resultado da comparação

    void iniciar();     // implementado em app.cpp
};
