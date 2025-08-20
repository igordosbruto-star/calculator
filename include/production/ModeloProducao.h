#pragma once

#include <string>
#include <vector>

// Estruturas de modelo de produção (BOM) para representar produtos
// compostos por várias partes e materiais.  Este cabeçalho define
// classes básicas para registrar modelos de produção com subestruturas.

namespace production {

// Representa um item de material necessário para uma parte da produção.
struct ItemMaterial {
    std::string nome;
    std::string unidade;  // ex.: "cm", "m", "unidade"
    double quantidade;
};

// Representa um componente de um produto (por exemplo, Estrutura A,
// Estrutura B).  Cada componente pode conter vários itens de material.
struct Componente {
    std::string nome;
    std::vector<ItemMaterial> materiais;
};

// ModeloProducao descreve um produto completo com sua lista de
// componentes.  Ele também armazena variantes (como tipos de tecido) e
// observações para permitir ajustes sem alterar a definição base.
class ModeloProducao {
public:
    ModeloProducao(const std::string& id, const std::string& nome);

    void adicionarComponente(const Componente& comp);
    const std::vector<Componente>& componentes() const;

    // Definir uma variante para um campo (ex.: tecido = "Veludo Rose Gold").
    void definirVariavel(const std::string& chave, const std::string& valor);
    const std::string& variavel(const std::string& chave) const;

private:
    std::string id_;
    std::string nome_;
    std::vector<Componente> componentes_;
    std::vector<std::pair<std::string, std::string>> variaveis_;
};

} // namespace production

