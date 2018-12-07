//
// Created by tuser on 18-12-7.
//
#include "sales.h"

double SALES::Sales::araverage(const double *ar, int n){
    double sum = 0;
    for (int i = 0; i < n; i++)
        sum += ar[i];
    return (sum / n);
}

double SALES::Sales::armax(const double *ar, int n) {
    double max = ar[0];
    for (int i = 1; i < n; i++)
        if (max < ar[i])
            max = ar[i];
    return max;
}

double SALES::Sales::armin(const double *ar, int n) {
    double min = ar[0];
    for (int i = 1; i < n; i++)
        if (min > ar[i])
            min = ar[i];
    return min;
}

SALES::Sales::Sales() {
    double ar[QUARTERS];
    for (int i = 0; i < QUARTERS; i++){
        std::cout << "sales #" << i+1 << ": ";
        std::cin >> ar[i];
        std::cin.get();
    }
    *this = Sales(ar, QUARTERS);
}

SALES::Sales::Sales(const double *ar, int n) {
    int size = n < QUARTERS ? n : QUARTERS;
    if (size < QUARTERS)
        for (int i = QUARTERS - size; i < QUARTERS; i++)
            sales[i] = 0;
    for (int i = 0; i < size; i++)
        sales[i] = ar[i];
    average = araverage(sales, size);
    max = armax(sales, size);
    min = armin(sales, size);
}

void SALES::Sales::showSales() const {
    for (int i = 0; i < QUARTERS; i++){
        std::cout << "Sales #" << i+1 << ": ";
        std::cout << sales[i] << std::endl;
    }
    std::cout << "Average: " << average << std::endl;
    std::cout << "Max: " << max << std::endl;
    std::cout << "Min: " << min << std::endl;
}