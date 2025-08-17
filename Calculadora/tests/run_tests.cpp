#include <cassert>

// Declara testes
void test_cli();
void test_persist();
void test_persist_io();
void test_extremos();
void test_corte();

// Executa todos os testes
int main() {
    test_cli();
    test_persist();
    test_persist_io();
    test_extremos();
    test_corte();
    return 0;
}
