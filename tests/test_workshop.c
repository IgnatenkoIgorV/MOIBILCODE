#include <stdio.h>
#include <assert.h>
#include <string.h>

// Тест 1: Проверка добавления мастерской
void test_add_workshop(void) {
    printf("  Test 3.1: Add workshop... ");
    Workshop w = {99, "Test Address", "Test Brands"};
    int result = add_workshop(&w);
    assert(result == 1);
    printf("PASSED\n");
}

// Тест 2: Проверка получения мастерской
void test_get_workshop(void) {
    printf("  Test 3.2: Get workshop... ");
    Workshop w;
    int result = get_workshop(99, &w);
    assert(result == 1);
    assert(w.number == 99);
    printf("PASSED\n");
}

// Тест 3: Проверка удаления мастерской
void test_delete_workshop(void) {
    printf("  Test 3.3: Delete workshop... ");
    int result = delete_workshop(99);
    assert(result == 1);
    printf("PASSED\n");
}

int main() {
    printf("\n=== Testing workshop.c ===\n");
    test_add_workshop();
    test_get_workshop();
    test_delete_workshop();
    printf("=== workshop.c tests PASSED ===\n\n");
    return 0;
}
