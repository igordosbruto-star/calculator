#include <cassert>

// Declara testes
void test_cli();
void test_persist();
void test_persist_io();
void test_extremos();
void test_corte();
void test_plano_dto();
void test_persist_helpers();

// Executa todos os testes
int main() {
    test_cli();
    test_persist();
    test_persist_io();
    test_extremos();
    test_corte();
    test_plano_dto();
    test_persist_helpers();
    return 0;
}

