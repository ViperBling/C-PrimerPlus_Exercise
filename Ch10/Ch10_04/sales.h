//
// Created by tuser on 18-12-7.
//

#ifndef SALES_H
#define SALES_H

#include <iostream>

namespace SALES {
    const int QUARTERS = 4;
    class Sales {
    private:
        double sales[QUARTERS];
        double average;
        double max;
        double min;
        double araverage(const double ar[], int n);
        double armax(const double ar[], int n);
        double armin(const double ar[], int n);
    public:
        Sales();
        Sales(const double ar[], int n = 0);
        void showSales() const;
    };
}


#endif // SALES_H
