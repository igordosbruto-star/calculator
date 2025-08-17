#pragma once

#include <vector>
#include <string>
#include "persist.h"
#include "Material.h"

struct Base { std::string nome; double valor = 0.0; };
struct Como { Base menor, maior; };

class App {
private:
    int dec = 2; // casas decimais para exibição
    Settings settings;
    std::vector<MaterialDTO> base;
    std::vector<Material> mats;

    void importarCSV();
    bool carregarJSON();
    void menuMateriais();
    void escolherPreco();
    void solicitarCortes();
    void exportar();

public:
    double preco = 0.0; // preço/m² escolhido (menor ou maior)
    Como q;             // resultado da comparação

    void iniciar();     // implementado em App.cpp
};

