#include <stdio.h>
#include <assert.h>
#include <string.h>

// Тест 1: Проверка добавления автомобиля
void test_add_car(void) {
    printf("  Test 4.1: Add car... ");
    Car c;
    strcpy(c.license_plate, "TEST01");
    strcpy(c.brand, "TestBrand");
    c.year = 2024;
    strcpy(c.owner_name, "Test Owner");
    strcpy(c.tech_passport, "TP999");
    strcpy(c.owner_address, "Test Address");
    int result = add_car(&c);
    assert(result == 1);
    printf("PASSED\n");
}

// Тест 2: Проверка получения автомобиля
void test_get_car(void) {
    printf("  Test 4.2: Get car... ");
    Car c;
    int result = get_car("TEST01", &c);
    assert(result == 1);
    assert(strcmp(c.brand, "TestBrand") == 0);
    printf("PASSED\n");
}

// Тест 3: Проверка удаления автомобиля
void test_delete_car(void) {
    printf("  Test 4.3: Delete car... ");
    int result = delete_car("TEST01");
    assert(result == 1);
    printf("PASSED\n");
}

int main() {
    printf("\n=== Testing car.c ===\n");
    test_add_car();
    test_get_car();
    test_delete_car();
    printf("=== car.c tests PASSED ===\n\n");
    return 0;
}
