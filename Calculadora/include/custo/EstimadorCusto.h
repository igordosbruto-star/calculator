#pragma once

#include <string>
#include <vector>

#include "custo/CustoParams.h"
#include "domain/MaterialBase.h"

// Item requisitado com identificação e medidas
struct ItemReq {
    std::string idMaterial;    // identificador do material
    std::string tipoMaterial;  // tipo do material (unitario/linear/cubico)
    double qtd = 0.0;          // quantidade necessária
    Medidas medidas;           // medidas relevantes
};

// Descrição de um item de corte
struct ItemCorte {
    std::string nome;          // identificação do corte
    double largura = 0.0;      // em metros
    double comprimento = 0.0;  // em metros
    double profundidade = 0.0; // em metros (opcional)
    double qtd = 0.0;          // quantidade de peças
    std::string idMaterial;    // material associado (opcional)
};

// Item de projeto com material já referenciado
struct ProjetoItem {
    ItemReq req;                   // requisição do item
    const MaterialBase* material;  // ponteiro para material existente
};

// Projeto composto por itens de materiais
struct ProjetoCusto {
    std::vector<ProjetoItem> materiais;  // itens de material do projeto
};

// Classe responsável por estimar custos
class EstimadorCusto {
public:
    // Calcula o custo de um material específico
    // Exemplo: custoMaterial(req, mat)
    double custoMaterial(const ItemReq& req, const MaterialBase& m) const;

    // Calcula o custo total de um projeto aplicando parâmetros globais
    // Exemplo: custoProjeto(prj, cfg)
    double custoProjeto(const ProjetoCusto& prj, const CustoParams& cfg) const;
};

