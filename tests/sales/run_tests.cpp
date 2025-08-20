#include "../test_runner.h"

void test_criar_pedido();
void test_listar_clientes();
void test_consulta_estoque();
void test_pedido_invalido();

int main() {
    return run_tests({
        test_criar_pedido,
        test_listar_clientes,
        test_consulta_estoque,
        test_pedido_invalido
    });
}
