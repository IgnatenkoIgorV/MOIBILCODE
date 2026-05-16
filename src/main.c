#include <stdio.h>
#include <string.h>
#include "../includes/auth.h"
#include "../includes/workshop.h"
#include "../includes/car.h"
#include "../includes/repair.h"
#include "../includes/report.h"

void show_menu_manager(void) {
    printf("\n╔══════════════════════════════════════╗\n");
    printf("║        MANAGER MENU                   ║\n");
    printf("╠══════════════════════════════════════╣\n");
    printf("║  1. Manage Workshops                  ║\n");
    printf("║  2. Manage Cars                       ║\n");
    printf("║  3. Manage Repairs                    ║\n");
    printf("║  4. Reports                           ║\n");
    printf("║  5. Driver Earnings                   ║\n");
    printf("║  6. Logout                            ║\n");
    printf("╚══════════════════════════════════════╝\n");
    printf("Choose: ");
}

void show_menu_master(void) {
    printf("\n╔══════════════════════════════════════╗\n");
    printf("║        MASTER MENU                    ║\n");
    printf("╠══════════════════════════════════════╣\n");
    printf("║  1. View My Repairs                   ║\n");
    printf("║  2. View My Earnings                  ║\n");
    printf("║  3. Logout                            ║\n");
    printf("╚══════════════════════════════════════╝\n");
    printf("Choose: ");
}

void manage_workshops(void) {
    int choice, number;
    Workshop w;
    
    do {
        printf("\n--- Workshops Management ---\n");
        printf("1. List workshops\n");
        printf("2. Add workshop\n");
        printf("3. Edit workshop\n");
        printf("4. Delete workshop\n");
        printf("5. Back\n");
        printf("Choose: ");
        scanf("%d", &choice);
        
        switch(choice) {
            case 1:
                list_workshops();
                break;
            case 2:
                printf("Number: "); scanf("%d", &w.number);
                printf("Address: "); scanf(" %[^\n]", w.address);
                printf("Car brands (comma separated): "); scanf(" %[^\n]", w.car_brands);
                if (add_workshop(&w)) printf("Workshop added!\n");
                else printf("Error adding workshop!\n");
                break;
            case 3:
                printf("Workshop number: "); scanf("%d", &number);
                if (get_workshop(number, &w)) {
                    printf("New address (%s): ", w.address); scanf(" %[^\n]", w.address);
                    printf("New car brands (%s): ", w.car_brands); scanf(" %[^\n]", w.car_brands);
                    if (update_workshop(&w)) printf("Workshop updated!\n");
                    else printf("Error updating!\n");
                } else printf("Workshop not found!\n");
                break;
            case 4:
                printf("Workshop number: "); scanf("%d", &number);
                if (delete_workshop(number)) printf("Workshop deleted!\n");
                else printf("Error deleting!\n");
                break;
        }
    } while(choice != 5);
}

void manage_cars(void) {
    int choice;
    Car c;
    char plate[10];
    
    do {
        printf("\n--- Cars Management ---\n");
        printf("1. List cars\n");
        printf("2. Add car\n");
        printf("3. Edit car\n");
        printf("4. Delete car\n");
        printf("5. Back\n");
        printf("Choose: ");
        scanf("%d", &choice);
        
        switch(choice) {
            case 1:
                list_cars();
                break;
            case 2:
                printf("License plate: "); scanf("%s", c.license_plate);
                printf("Brand: "); scanf(" %[^\n]", c.brand);
                printf("Year: "); scanf("%d", &c.year);
                printf("Owner name: "); scanf(" %[^\n]", c.owner_name);
                printf("Tech passport: "); scanf("%s", c.tech_passport);
                printf("Owner address: "); scanf(" %[^\n]", c.owner_address);
                if (add_car(&c)) printf("Car added!\n");
                else printf("Error adding car!\n");
                break;
            case 3:
                printf("License plate: "); scanf("%s", plate);
                if (get_car(plate, &c)) {
                    printf("New brand (%s): ", c.brand); scanf(" %[^\n]", c.brand);
                    printf("New year (%d): ", c.year); scanf("%d", &c.year);
                    printf("New owner name (%s): ", c.owner_name); scanf(" %[^\n]", c.owner_name);
                    if (update_car(&c)) printf("Car updated!\n");
                    else printf("Error updating!\n");
                } else printf("Car not found!\n");
                break;
            case 4:
                printf("License plate: "); scanf("%s", plate);
                if (delete_car(plate)) printf("Car deleted!\n");
                else printf("Error deleting!\n");
                break;
        }
    } while(choice != 5);
}

void manage_repairs(void) {
    int choice, id;
    Repair r;
    
    do {
        printf("\n--- Repairs Management ---\n");
        printf("1. List repairs\n");
        printf("2. Add repair\n");
        printf("3. Edit repair\n");
        printf("4. Delete repair\n");
        printf("5. Back\n");
        printf("Choose: ");
        scanf("%d", &choice);
        
        switch(choice) {
            case 1:
                list_repairs();
                break;
            case 2:
                printf("Workshop number: "); scanf("%d", &r.workshop_number);
                printf("Start date (YYYY-MM-DD): "); scanf("%s", r.start_date);
                printf("End date (YYYY-MM-DD): "); scanf("%s", r.end_date);
                printf("License plate: "); scanf("%s", r.license_plate);
                printf("Repair type: "); scanf(" %[^\n]", r.repair_type);
                printf("Cost: "); scanf("%lf", &r.cost);
                printf("Master name: "); scanf(" %[^\n]", r.master_name);
                if (add_repair(&r)) printf("Repair added!\n");
                else printf("Error adding repair!\n");
                break;
            case 3:
                printf("Repair ID: "); scanf("%d", &id);
                if (get_repair(id, &r)) {
                    printf("New cost (%.2f): ", r.cost); scanf("%lf", &r.cost);
                    if (update_repair(&r)) printf("Repair updated!\n");
                    else printf("Error updating!\n");
                } else printf("Repair not found!\n");
                break;
            case 4:
                printf("Repair ID: "); scanf("%d", &id);
                if (delete_repair(id)) printf("Repair deleted!\n");
                else printf("Error deleting!\n");
                break;
        }
    } while(choice != 5);
}

void show_reports(void) {
    int choice, num;
    char start_date[11], end_date[11], name[100];
    
    do {
        printf("\n--- Reports ---\n");
        printf("1. Workshop repairs\n");
        printf("2. Master repairs\n");
        printf("3. Repairs by brand\n");
        printf("4. Workshop statistics\n");
        printf("5. Best workshop\n");
        printf("6. Back\n");
        printf("Choose: ");
        scanf("%d", &choice);
        
        switch(choice) {
            case 1:
                printf("Workshop number: "); scanf("%d", &num);
                report_workshop_repairs(num);
                break;
            case 2:
                printf("Master name: "); scanf(" %[^\n]", name);
                report_master_repairs(name);
                break;
            case 3:
                report_repairs_by_brand();
                break;
            case 4:
                report_workshop_stats();
                break;
            case 5:
                report_best_workshop();
                break;
        }
    } while(choice != 6);
}

void driver_earnings_menu(void) {
    int choice;
    char start_date[11], end_date[11], name[100];
    User* current = get_current_user();
    
    do {
        printf("\n--- Driver Earnings ---\n");
        printf("1. My earnings (period)\n");
        if (strcmp(current->role, "manager") == 0) {
            printf("2. All drivers earnings (period)\n");
            printf("3. Specific driver earnings (period)\n");
        }
        printf("4. Back\n");
        printf("Choose: ");
        scanf("%d", &choice);
        
        switch(choice) {
            case 1:
                printf("Start date (YYYY-MM-DD): "); scanf("%s", start_date);
                printf("End date (YYYY-MM-DD): "); scanf("%s", end_date);
                printf("Earnings: %.2f\n", calculate_driver_earnings(current->full_name, start_date, end_date));
                break;
            case 2:
                if (strcmp(current->role, "manager") == 0) {
                    printf("Start date (YYYY-MM-DD): "); scanf("%s", start_date);
                    printf("End date (YYYY-MM-DD): "); scanf("%s", end_date);
                    calculate_all_earnings(start_date, end_date);
                }
                break;
            case 3:
                if (strcmp(current->role, "manager") == 0) {
                    printf("Driver name: "); scanf(" %[^\n]", name);
                    printf("Start date (YYYY-MM-DD): "); scanf("%s", start_date);
                    printf("End date (YYYY-MM-DD): "); scanf("%s", end_date);
                    printf("Earnings: %.2f\n", calculate_driver_earnings(name, start_date, end_date));
                }
                break;
        }
    } while(choice != 4);
}

int main() {
    User user;
    char login[50], password[50];
    int choice;
    
    printf("\n========================================\n");
    printf("   WELCOME TO AUTOMASTERS SYSTEM\n");
    printf("========================================\n");
    
    while(1) {
        printf("\nLogin: ");
        scanf("%s", login);
        printf("Password: ");
        scanf("%s", password);
        
        if (auth_login(login, password, &user)) {
            printf("\n✅ Welcome, %s!\n", user.full_name);
            printf("Role: %s\n", user.role);
            
            if (strcmp(user.role, "manager") == 0) {
                do {
                    show_menu_manager();
                    scanf("%d", &choice);
                    switch(choice) {
                        case 1: manage_workshops(); break;
                        case 2: manage_cars(); break;
                        case 3: manage_repairs(); break;
                        case 4: show_reports(); break;
                        case 5: driver_earnings_menu(); break;
                        case 6: printf("Logging out...\n"); break;
                        default: printf("Invalid choice!\n");
                    }
                } while(choice != 6);
            } 
            else if (strcmp(user.role, "master") == 0) {
                do {
                    show_menu_master();
                    scanf("%d", &choice);
                    switch(choice) {
                        case 1: report_master_repairs(user.full_name); break;
                        case 2: driver_earnings_menu(); break;
                        case 3: printf("Logging out...\n"); break;
                        default: printf("Invalid choice!\n");
                    }
                } while(choice != 3);
            }
            auth_logout();
        } else {
            printf("❌ Invalid login or password!\n");
        }
        
        printf("\nContinue? (1-yes/0-no): ");
        scanf("%d", &choice);
        if (choice == 0) break;
    }
    
    printf("\nGoodbye!\n");
    return 0;
}
