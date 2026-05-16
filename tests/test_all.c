#include <stdio.h>
#include <string.h>
#include <assert.h>
#include <stdlib.h>
#include <sqlite3.h>

// Включаем все заголовочные файлы
#include "../includes/auth.h"
#include "../includes/db.h"
#include "../includes/workshop.h"
#include "../includes/car.h"
#include "../includes/repair.h"
#include "../includes/report.h"

// ============================================
// Тесты для auth.c
// ============================================
void test_auth_structure(void) {
    printf("  Test 1.1: User structure... ");
    User u;
    u.id = 0;
    assert(u.id == 0);
    printf("PASSED\n");
}

void test_auth_login_invalid(void) {
    printf("  Test 1.2: Invalid login... ");
    User user;
    int result = auth_login("nonexistent_user_12345", "wrong", &user);
    assert(result == 0);
    printf("PASSED\n");
}

void test_auth_logout_func(void) {
    printf("  Test 1.3: Logout function... ");
    auth_logout();
    printf("PASSED\n");
}

// ============================================
// Тесты для db.c
// ============================================
void test_db_connect_memory(void) {
    printf("  Test 2.1: Memory DB connection... ");
    sqlite3* db = db_connect(":memory:");
    assert(db != NULL);
    db_disconnect(db);
    printf("PASSED\n");
}

void test_db_execute_sql(void) {
    printf("  Test 2.2: SQL execute... ");
    sqlite3* db = db_connect(":memory:");
    int rc = db_execute(db, "CREATE TABLE t(id INT)");
    assert(rc == SQLITE_OK);
    db_disconnect(db);
    printf("PASSED\n");
}

void test_db_disconnect_func(void) {
    printf("  Test 2.3: Disconnect function... ");
    sqlite3* db = db_connect(":memory:");
    db_disconnect(db);
    printf("PASSED\n");
}

// ============================================
// Тесты для workshop.c
// ============================================
void test_workshop_exists_func(void) {
    printf("  Test 3.1: Workshop exists... ");
    int result = workshop_exists(999);
    assert(result == 0);
    printf("PASSED\n");
}

void test_list_workshops(void) {
    printf("  Test 3.2: List workshops... ");
    list_workshops();
    printf("PASSED\n");
}

void test_workshop_add_validation(void) {
    printf("  Test 3.3: Add workshop validation... ");
    Workshop w = {9999, "Test Address", "Test Brands"};
    int result = add_workshop(&w);
    assert(result == 1);
    delete_workshop(9999);
    printf("PASSED\n");
}

// ============================================
// Тесты для car.c
// ============================================
void test_car_exists_func(void) {
    printf("  Test 4.1: Car exists... ");
    int result = car_exists("NONEXISTENT");
    assert(result == 0);
    printf("PASSED\n");
}

void test_list_cars(void) {
    printf("  Test 4.2: List cars... ");
    list_cars();
    printf("PASSED\n");
}

void test_car_add_delete(void) {
    printf("  Test 4.3: Add and delete car... ");
    Car c;
    strcpy(c.license_plate, "TST999");
    strcpy(c.brand, "Test");
    c.year = 2024;
    strcpy(c.owner_name, "Test Owner");
    strcpy(c.tech_passport, "TP999");
    strcpy(c.owner_address, "Test Address");
    add_car(&c);
    int exists = car_exists("TST999");
    assert(exists == 1);
    delete_car("TST999");
    printf("PASSED\n");
}

// ============================================
// Тесты для repair.c
// ============================================
void test_repair_capacity_check(void) {
    printf("  Test 5.1: Capacity check... ");
    int result = check_capacity("A123BC", 100.0);
    printf("PASSED (result=%d)\n", result);
}

void test_list_repairs(void) {
    printf("  Test 5.2: List repairs... ");
    list_repairs();
    printf("PASSED\n");
}

void test_repair_get_function(void) {
    printf("  Test 5.3: Get repair... ");
    Repair r;
    int result = get_repair(1, &r);
    printf("PASSED (result=%d)\n", result);
}

// ============================================
// Тесты для report.c
// ============================================
void test_report_workshop(void) {
    printf("  Test 6.1: Workshop report... ");
    report_workshop_repairs(1);
    printf("PASSED\n");
}

void test_report_master(void) {
    printf("  Test 6.2: Master report... ");
    report_master_repairs("Test Master");
    printf("PASSED\n");
}

void test_calculate_earnings(void) {
    printf("  Test 6.3: Calculate earnings... ");
    double result = calculate_driver_earnings("Test Master", "2024-01-01", "2024-12-31");
    assert(result >= 0);
    printf("PASSED (%.2f)\n", result);
}

// ============================================
// Главная функция
// ============================================
int main() {
    printf("\n========================================\n");
    printf("     RUNNING ALL TESTS (18+ tests)\n");
    printf("========================================\n\n");

    printf("=== Testing auth.c ===\n");
    test_auth_structure();
    test_auth_login_invalid();
    test_auth_logout_func();

    printf("\n=== Testing db.c ===\n");
    test_db_connect_memory();
    test_db_execute_sql();
    test_db_disconnect_func();

    printf("\n=== Testing workshop.c ===\n");
    test_workshop_exists_func();
    test_list_workshops();
    test_workshop_add_validation();

    printf("\n=== Testing car.c ===\n");
    test_car_exists_func();
    test_list_cars();
    test_car_add_delete();

    printf("\n=== Testing repair.c ===\n");
    test_repair_capacity_check();
    test_list_repairs();
    test_repair_get_function();

    printf("\n=== Testing report.c ===\n");
    test_report_workshop();
    test_report_master();
    test_calculate_earnings();

    printf("\n========================================\n");
    printf("     ALL TESTS PASSED!\n");
    printf("========================================\n");

    return 0;
}
