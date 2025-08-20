#include "../test_runner.h"

void test_lancamento();
void test_filtro();
void test_tipo_string();
void test_serialize();
void test_repo_sum();
void test_repo_validacao();
void test_report_mes();
void test_repo_load_invalid_json();
void test_repo_save_invalid_json_preserves_existing();

int main() {
    return run_tests({
        test_lancamento,
        test_filtro,
        test_tipo_string,
        test_serialize,
        test_repo_sum,
        test_repo_validacao,
        test_report_mes,
        test_repo_load_invalid_json,
        test_repo_save_invalid_json_preserves_existing
    });
}
