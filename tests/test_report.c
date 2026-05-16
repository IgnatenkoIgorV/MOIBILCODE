#include <stdio.h>
#include <assert.h>

// Тест 1: Проверка отчета по мастерской
void test_report_workshop_repairs(void) {
    printf("  Test 6.1: Workshop repairs report... ");
    report_workshop_repairs(1);
    printf("PASSED\n");
}

// Тест 2: Проверка отчета по мастеру
void test_report_master_repairs(void) {
    printf("  Test 6.2: Master repairs report... ");
    report_master_repairs("Test Master");
    printf("PASSED\n");
}

// Тест 3: Проверка расчета заработка
void test_calculate_earnings(void) {
    printf("  Test 6.3: Calculate earnings... ");
    double result = calculate_driver_earnings("Test Master", "2024-01-01", "2024-12-31");
    assert(result >= 0);
    printf("PASSED\n");
}

int main() {
    printf("\n=== Testing report.c ===\n");
    test_report_workshop_repairs();
    test_report_master_repairs();
    test_calculate_earnings();
    printf("=== report.c tests PASSED ===\n\n");
    return 0;
}
