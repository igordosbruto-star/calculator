#pragma once

#include <vector>
#include <string>
#include "core/persist.h"
#include "Material.h"
#include "core.h"
#include "ApplicationCore.h"
namespace duke {

class App {
private:
    int dec = 2; // casas decimais para exibição
    Settings settings;
    std::vector<MaterialDTO> base;
    std::vector<Material> mats;
    ApplicationCore core; // camada de regras de negócio

    void importarCSV();
    bool carregar();
    void menuMateriais();
    void escolherPreco();
    void solicitarCortes();
    void exportar();
    void criarMaterial();
    void listarCortes();
    void compararMateriais();
    void finAdicionar();
    void finListar();
    void finSomar();

public:
    double preco = 0.0;      // preço/m² escolhido (menor ou maior)
    core::Como q;            // resultado da comparação

    // Inicia o aplicativo
    // autoMode=true usa automaticamente o material mais barato
    void iniciar(bool autoMode = false);     // implementado em App.cpp
};

} // namespace duke
