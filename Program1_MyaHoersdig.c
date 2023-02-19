/*
Mya Hoersdig
EECS 348 Lab3 Problem 1
Given 12 monthly sales numbers in an input file. Using functions, generate a tabular sales report 
and also the sales summary report (as shown in the sample output). Your output should include 
the below:   
 Sales report (month and sales in two columns) 
 minimum, maximum, and average of the monthly sales. 
 six-month moving averages. 
 monthly sales report from highest to lowest. 
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define NUM_MONTHS 12

char* month_name(int num) {
    static char *months[] = {
        "January", "February", "March", "April",
        "May", "June", "July", "August",
        "September", "October", "November", "December"
    };
    return months[num - 1];
}

void print_sales_report(float sales[]) {
    printf("\nMonthly sales report for 2022:\n");
    printf("Month\t\tSales\n");
    for (int i = 0; i < NUM_MONTHS; i++) {
        printf("%-5s\t$%.2f\n", month_name(i+1), sales[i]);
    }
}

void print_summary(float sales[]) {
    float min_sales = sales[0];
    float max_sales = sales[0];
    int month;
    float total_sales = 0;

    for (int i = 0; i < NUM_MONTHS; i++) {
        if (sales[i] < min_sales) {
            min_sales = sales[i];
            month = i;
        }
        if (sales[i] > max_sales) {
            max_sales = sales[i];
            month = i;
        }
        total_sales += sales[i];
    }

    double avg_sales = (double) total_sales / NUM_MONTHS;

    printf("\nSales summary:\n");
    printf("Minimum Sales: $%.2f   (%s)\n", min_sales, month_name(month-10));
    printf("Maximum Sales: $%.2f   (%s)\n", max_sales, month_name(month+1));
    printf("Average Sales: $%.2f\n", avg_sales);
}

void six_month_average(float sales[]) {
    printf("\nSix-Month Moving Average Report:\n");
    for (int i = 0; i <= NUM_MONTHS-6; i++) {
        double moving_avg = 0;
        for (int j = i; j < i+6; j++) {
            moving_avg += sales[j];
        }
        moving_avg /= 6;
        printf("%s\t-  %s\t$%.2f\n", month_name(i+1), month_name(i+6), moving_avg);
    }
}

void print_sales(float sales[]) {
    float temp[NUM_MONTHS];
    for (int i = 0; i < NUM_MONTHS; i++) {
        temp[i] = sales[i];
    }
    printf("\nSales Report (Highest to Lowest):\n");
    printf("Month\t\tSales\n");

    for (int i = 0; i < NUM_MONTHS; i++) {
        int max_index = i;
        for (int j = i + 1; j < NUM_MONTHS; j++) {
            if (temp[j] > temp[max_index] ||
                (temp[j] == temp[max_index] && j < max_index)) {
                max_index = j;
            }
        }
        float temp_sales = temp[i];
        temp[i] = temp[max_index];
        temp[max_index] = temp_sales;

        int max_indices[NUM_MONTHS];
        int num_max = 0;
        for (int j = 0; j < NUM_MONTHS; j++) {
            if (sales[j] == temp[i]) {
                max_indices[num_max++] = j;
            }
        }

        for (int j = 0; j < num_max; j++) {
            printf("%-5s\t$%.2f\n", month_name(max_indices[j]+1), temp[i]);
        }
    }
}

int main() {
    char file_name[100], line[100];
    FILE *input_file;

    printf("Enter file name: ");
    scanf("%s", file_name);

    input_file = fopen(file_name, "r");

    if(NULL == file_name) {
        printf("Invalid File");
    }

    float sales[NUM_MONTHS];
    for (int i = 0; i < NUM_MONTHS; i++) {
        fscanf(input_file, "%e", &sales[i]);
    }

    fclose(input_file);
    
    print_sales_report(sales); 
    print_summary(sales);
    six_month_average(sales);
    print_sales(sales);
}

