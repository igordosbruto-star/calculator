#pragma once

#include <string>
#include <vector>
#include "domain/MaterialBase.h"

// Item de material dentro de um projeto
struct ProjetoItemMaterial {
    std::string idMaterial;    // identificador do material
    double quantidade = 0.0;   // quantidade necessária
    Medidas medidas;           // medidas relevantes
    double custoUnitario = 0.0; // custo de cada unidade
};

// Item de corte associado a um material
struct ProjetoItemCorte {
    std::string idMaterial;    // material do corte
    double largura = 0.0;      // largura em metros
    double comprimento = 0.0;  // comprimento em metros
    double quantidade = 0.0;   // número de peças
    double custoUnitario = 0.0;// custo por peça
};

// Representa um projeto completo
class Projeto {
public:
    std::string id;                 // identificador único
    std::string nome;               // nome do projeto
    std::vector<ProjetoItemMaterial> materiais; // itens de material
    std::vector<ProjetoItemCorte> cortes;       // itens de corte

    // Adiciona um material ao projeto. Retorna falso em caso de validação falha.
    // Exemplo:
    //   ProjetoItemMaterial it{"madeira", 2, {}, 10.0};
    //   prj.adicionarMaterial(it);
    bool adicionarMaterial(const ProjetoItemMaterial& item);

    // Adiciona um corte ao projeto. Retorna falso se medidas inválidas.
    bool adicionarCorte(const ProjetoItemCorte& item);

    // Remove todos os itens associados ao idMaterial informado.
    bool removerItem(const std::string& idMaterial);

    // Calcula o custo total do projeto.
    double resumoCusto() const;
};

