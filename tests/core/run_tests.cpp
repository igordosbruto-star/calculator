#include "../test_runner.h"

void test_atomic_write_permission();
void test_restore_backup();
void test_monthly_summary();
void test_generate_report();
void test_overdue_alert();

int main() {
    return run_tests({
        test_atomic_write_permission,
        test_restore_backup,
        test_monthly_summary,
        test_generate_report,
        test_overdue_alert
    });
}
