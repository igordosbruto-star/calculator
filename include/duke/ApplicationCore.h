#pragma once

#include <vector>
#include <string>
#include "core/persist.h"
#include "Material.h"
#include "core.h"
#include "comparison.h"
#include "Customer.h"
#include "Order.h"
#include "finance/Repo.h"

namespace duke {

// Camada central de operacoes do aplicativo sem interacao direta com o usuario.
class ApplicationCore {
public:
    // Carrega materiais a partir de um arquivo JSON. Retorna false se menos de dois materiais forem carregados.
    // Exemplo:
    //   ApplicationCore core;
    //   std::vector<MaterialDTO> base;
    //   std::vector<Material> mats;
    //   bool ok = core.carregarJSON(base, mats);
    bool carregarJSON(std::vector<MaterialDTO>& base, std::vector<Material>& mats);

    // Lista materiais disponíveis. O retorno é uma cópia dos dados para exibição.
    // Exemplo:
    //   auto itens = core.listarMateriais(base);
    std::vector<MaterialDTO> listarMateriais(const std::vector<MaterialDTO>& base) const;

    // Resultado da comparação de materiais com destaque para menor e maior preço por m².
    // Compara materiais selecionados pelos índices (base 0).
    // Exemplo:
    //   auto r = core.compararMateriais(mats, {0,1});
    std::vector<comparison::MaterialComparado> compararMateriais(
        const std::vector<Material>& mats, const std::vector<int>& ids) const;

    // ----- APIs do módulo de vendas -----
    // Carrega materiais, clientes e pedidos usando os arquivos JSON padrão.
    // Exemplo:
    //   ApplicationCore core;
    //   core.carregarJSON();
    bool carregarJSON();

    // Cria e persiste um novo pedido.
    // Exemplo:
    //   core.criarPedido("Ana", "Produto", 2);
    bool criarPedido(const std::string& cliente, const std::string& item, int quantidade);

    // Lista clientes cadastrados.
    std::vector<Customer> listarClientes() const;

    // Lista pedidos registrados.
    std::vector<Order> listarPedidos() const;

    // Consulta o estoque de materiais carregado.
    std::vector<MaterialDTO> listarEstoque() const;

    // ----- APIs do módulo financeiro -----
    // Carrega lançamentos financeiros do repositório padrão.
    bool carregarFinanceiro();

    // Gera próximo identificador de lançamento.
    std::string proximoIdLancamento();

    // Adiciona e persiste um novo lançamento financeiro.
    bool adicionarLancamento(const finance::Lancamento& l);

    // Lista lançamentos conforme filtros informados.
    std::vector<finance::Lancamento> listarLancamentos(const finance::Filtro& f) const;

    // Soma valores dos lançamentos filtrados.
    double somarLancamentos(const finance::Filtro& f) const;

private:
    std::vector<MaterialDTO> base_;
    std::vector<Material> mats_;
    std::vector<Customer> clientes_;
    std::vector<Order> pedidos_;
    int nextId_ = 1;
    finance::FinanceRepo finRepo_;
};

} // namespace duke

