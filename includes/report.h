#ifndef REPORT_H
#define REPORT_H

void report_workshop_repairs(int workshop_number);
void report_master_repairs(const char* master_name);
void report_repairs_by_brand(void);
void report_workshop_stats(void);
void report_best_workshop(void);
double calculate_driver_earnings(const char* master_name, const char* start_date, const char* end_date);
void calculate_all_earnings(const char* start_date, const char* end_date);

#endif
