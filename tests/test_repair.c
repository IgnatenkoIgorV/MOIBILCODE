#include <stdio.h>
#include <assert.h>
#include <string.h>

// Тест 1: Проверка добавления работы
void test_add_repair(void) {
    printf("  Test 5.1: Add repair... ");
    Repair r;
    r.workshop_number = 1;
    strcpy(r.start_date, "2024-01-01");
    strcpy(r.end_date, "2024-01-02");
    strcpy(r.license_plate, "TEST01");
    strcpy(r.repair_type, "Test Repair");
    r.cost = 100.0;
    strcpy(r.master_name, "Test Master");
    int result = add_repair(&r);
    assert(result == 0);
    printf("PASSED\n");
}

// Тест 2: Проверка получения работы
void test_get_repair(void) {
    printf("  Test 5.2: Get repair... ");
    Repair r;
    int result = get_repair(1, &r);
    assert(result == 0);
    printf("PASSED\n");
}

// Тест 3: Проверка проверки грузоподъемности
void test_check_capacity(void) {
    printf("  Test 5.3: Check capacity... ");
    int result = check_capacity("TEST01", 100.0);
    assert(result == 0);
    printf("PASSED\n");
}

int main() {
    printf("\n=== Testing repair.c ===\n");
    test_add_repair();
    test_get_repair();
    test_check_capacity();
    printf("=== repair.c tests PASSED ===\n\n");
    return 0;
}
