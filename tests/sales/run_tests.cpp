#include "../test_runner.h"

void test_criar_pedido();
void test_listar_clientes();
void test_consulta_estoque();

int main() {
    return run_tests({
        test_criar_pedido,
        test_listar_clientes,
        test_consulta_estoque
    });
}
