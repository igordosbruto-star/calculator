#include <cassert>
#include <cstdlib>

void test_lerOpcao12();
void test_adicionarMaterial();
void test_importarCSV_ignore();
void test_exportar_ignore();
void test_parseArgs_unknown();
void test_menu_key_widget_calls_core();
void test_main_window_button_calls_bridge();

int main() {
    test_lerOpcao12();
    test_adicionarMaterial();
    test_importarCSV_ignore();
    test_exportar_ignore();
    test_parseArgs_unknown();
    test_menu_key_widget_calls_core();
    test_main_window_button_calls_bridge();
    int gui_res = std::system("./gui_mainwindow.test");
    assert(gui_res == 0);
    return 0;
}

