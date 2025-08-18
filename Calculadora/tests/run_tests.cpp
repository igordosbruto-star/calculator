#include <cassert>

// Declara testes
void test_cli();
void test_persist();
void test_persist_io();
void test_persist_migration();
void test_extremos();
void test_corte();
void test_plano_dto();
void test_persist_helpers();
void test_plano_io();
void test_plano_index();
void test_data_path();
void test_domain_material();
void test_material_factory();
void test_estimador_custo();
void test_projeto();
void test_projeto_custo();
void test_tempo();

// Executa todos os testes
int main() {
    test_cli();
    test_persist();
    test_persist_io();
    test_persist_migration();
    test_extremos();
    test_corte();
    test_plano_dto();
    test_persist_helpers();
    test_plano_io();
    test_plano_index();
    test_data_path();
    test_domain_material();
    test_material_factory();
    test_estimador_custo();
    test_projeto();
    test_projeto_custo();
    test_tempo();
    return 0;
}
