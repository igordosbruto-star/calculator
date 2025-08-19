#include <cassert>

void test_lerOpcao12();
void test_adicionarMaterial();
void test_importarCSV_ignore();
void test_exportar_ignore();
void test_parseArgs_unknown();
void test_menu_key_widget_calls_core();

int main() {
    test_lerOpcao12();
    test_adicionarMaterial();
    test_importarCSV_ignore();
    test_exportar_ignore();
    test_parseArgs_unknown();
    test_menu_key_widget_calls_core();
    return 0;
}

