#include "../test_runner.h"

// Declara testes
void test_cli();
void test_persist();
void test_persist_io();
void testPersistGolden();
void test_persist_migration();
void test_settings_migration();
void test_extremos();
void test_extremos_vazio();
void test_corte();
void test_duke_api();
void test_plano_dto();
void test_persist_helpers();
void test_plano_io();
void test_plano_index();
void test_data_path();
void test_domain_material();
void test_material_factory();
void testValidarMaterialPorTipo();
void test_material_mostrar();
void test_estimador_custo();
void test_projeto();
void test_projeto_custo();
void test_tempo();
void test_menu();
void test_application_core();
void test_comparison();

int main() {
    return run_tests({
        test_cli,
        test_persist,
        test_persist_io,
        testPersistGolden,
        test_persist_migration,
        test_settings_migration,
        test_extremos,
        test_extremos_vazio,
        test_corte,
        test_duke_api,
        test_plano_dto,
        test_persist_helpers,
        test_plano_io,
        test_plano_index,
        test_data_path,
        test_domain_material,
        test_material_factory,
        testValidarMaterialPorTipo,
        test_material_mostrar,
        test_estimador_custo,
        test_projeto,
        test_projeto_custo,
        test_tempo,
        test_menu,
        test_application_core,
        test_comparison
    });
}
