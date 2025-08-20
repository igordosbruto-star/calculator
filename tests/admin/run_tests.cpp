#include "../test_runner.h"

void test_add_transaction();
void test_list_transactions();
void test_sum_transactions();
void test_suppliers();

int main() {
    return run_tests({
        test_add_transaction,
        test_list_transactions,
        test_sum_transactions,
        test_suppliers
    });
}
