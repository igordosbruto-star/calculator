#include "../test_runner.h"

void test_designer_create_project();
void test_designer_load_project();
void test_designer_export_bom();

int main() {
    return run_tests({
        test_designer_create_project,
        test_designer_load_project,
        test_designer_export_bom
    });
}
