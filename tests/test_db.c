#include <stdio.h>
#include <assert.h>
#include <sqlite3.h>

// Тест 1: Проверка подключения к БД
void test_db_connect(void) {
    printf("  Test 2.1: Database connection... ");
    sqlite3* db = db_connect(":memory:");
    assert(db != NULL);
    db_disconnect(db);
    printf("PASSED\n");
}

// Тест 2: Проверка выполнения SQL
void test_db_execute(void) {
    printf("  Test 2.2: SQL execute... ");
    sqlite3* db = db_connect(":memory:");
    int rc = db_execute(db, "CREATE TABLE test(id INTEGER)");
    assert(rc == SQLITE_OK);
    db_disconnect(db);
    printf("PASSED\n");
}

// Тест 3: Проверка закрытия соединения
void test_db_disconnect(void) {
    printf("  Test 2.3: Database disconnect... ");
    sqlite3* db = db_connect(":memory:");
    db_disconnect(db);
    printf("PASSED\n");
}

int main() {
    printf("\n=== Testing db.c ===\n");
    test_db_connect();
    test_db_execute();
    test_db_disconnect();
    printf("=== db.c tests PASSED ===\n\n");
    return 0;
}
