#include "ApplicationCore.h"
#include "core/persist.h"
#include <filesystem>
#include <vector>
#include <cassert>

// Testa criação de pedido
void test_criar_pedido() {
    using namespace duke;
    std::filesystem::remove_all("tmp_sales");
    Persist::Config cfg; cfg.baseDir = "tmp_sales"; Persist::setConfig(cfg);
    std::vector<MaterialDTO> mats{{"Prod", 10.0, 1.0, 1.0, "linear"}};
    Persist::saveJSON("materiais.json", mats);
    std::vector<Customer> clientes{Customer{"Ana"}};
    Persist::saveJSONVec("clientes.json", clientes, "clientes");

    ApplicationCore core;
    core.carregarJSON();
    assert(core.criarPedido("Ana", "Prod", 1));
    auto pedidos = core.listarPedidos();
    assert(pedidos.size() == 1);
    assert(pedidos[0].cliente == "Ana");
    std::filesystem::remove_all("tmp_sales");
}

// Testa listagem de clientes
void test_listar_clientes() {
    using namespace duke;
    std::filesystem::remove_all("tmp_sales_cli");
    Persist::Config cfg; cfg.baseDir = "tmp_sales_cli"; Persist::setConfig(cfg);
    std::vector<Customer> clientes{Customer{"Bia"}, Customer{"Carlos"}};
    Persist::saveJSONVec("clientes.json", clientes, "clientes");
    Persist::saveJSON("materiais.json", std::vector<MaterialDTO>{{"X",1,1,1,"linear"}});

    ApplicationCore core; core.carregarJSON();
    auto lista = core.listarClientes();
    assert(lista.size() == 2);
    assert(lista[0].nome == "Bia");
    std::filesystem::remove_all("tmp_sales_cli");
}

// Testa consulta de estoque
void test_consulta_estoque() {
    using namespace duke;
    std::filesystem::remove_all("tmp_sales_inv");
    Persist::Config cfg; cfg.baseDir = "tmp_sales_inv"; Persist::setConfig(cfg);
    std::vector<MaterialDTO> mats{{"Estoque", 5.0, 1.0, 1.0, "linear"}};
    Persist::saveJSON("materiais.json", mats);

    ApplicationCore core; core.carregarJSON();
    auto estoque = core.listarEstoque();
    assert(estoque.size() == 1);
    assert(estoque[0].nome == "Estoque");
    std::filesystem::remove_all("tmp_sales_inv");
}
