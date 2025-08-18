#pragma once

#include <string>
#include <vector>
#include "domain/MaterialBase.h"
#include "custo/CustoParams.h"

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

// Subtotal de custo para um item específico
struct ResumoCustoItem {
    std::string id;   // identificador do item
    double subtotal = 0.0; // custo calculado
};

// Resumo completo de custo do projeto
struct ResumoCustoProjeto {
    std::vector<ResumoCustoItem> itens; // lista de subtotais
    double total = 0.0;                 // total final com parâmetros globais
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

    // Calcula custos detalhados do projeto usando EstimadorCusto.
    // Exemplo:
    //   CustoParams cfg{0.05, 0.1, 0.05, 0.2, 2};
    //   auto resumo = prj.calcularCustos(cfg);
    ResumoCustoProjeto calcularCustos(const CustoParams& params) const;
};

