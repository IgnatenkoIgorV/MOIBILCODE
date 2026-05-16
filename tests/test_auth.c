#include <stdio.h>
#include <string.h>
#include <assert.h>
#include <sqlite3.h>

// Тест 1: Проверка структуры User
void test_user_structure(void) {
    printf("  Test 1.1: User structure size... ");
    assert(sizeof(User) > 0);
    printf("PASSED\n");
}

// Тест 2: Проверка auth_login с неверными данными
void test_auth_login_invalid(void) {
    printf("  Test 1.2: Auth login invalid... ");
    User user;
    int result = auth_login("nonexistent", "wrong", &user);
    assert(result == 0);
    printf("PASSED\n");
}

// Тест 3: Проверка auth_logout
void test_auth_logout(void) {
    printf("  Test 1.3: Auth logout... ");
    auth_logout();
    User* current = get_current_user();
    assert(current->id == 0);
    printf("PASSED\n");
}

int main() {
    printf("\n=== Testing auth.c ===\n");
    test_user_structure();
    test_auth_login_invalid();
    test_auth_logout();
    printf("=== auth.c tests PASSED ===\n\n");
    return 0;
}
