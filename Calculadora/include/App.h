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
    void criarMaterial();
    void listarCortes();
    void compararMateriais();

public:
    double preco = 0.0; // preço/m² escolhido (menor ou maior)
    Como q;             // resultado da comparação

    // Inicia o aplicativo
    // autoMode=true usa automaticamente o material mais barato
    void iniciar(bool autoMode = false);     // implementado em App.cpp
};

