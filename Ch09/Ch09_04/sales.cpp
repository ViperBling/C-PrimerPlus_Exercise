//
// Created by tuser on 18-12-4.
//
#include <iostream>
#include "sales.h"

namespace SALES{
    using std::cout;
    using std::cin;
    using std::endl;

    static double araverage(const double ar[], int n)
    {
        double sum = 0;
        for (int i = 0; i < n; i++)
            sum += ar[i];
        return (sum / n);
    }

    static double armax(const double ar[], int n)
    {
        double max = ar[0];
        for (int i = 0; i < n; i++)
            if (max < ar[i])
                max = ar[i];
        return max;
    }

    static double armin(const double ar[], int n)
    {
        double min = ar[0];
        for (int i = 0; i < n; i++)
            if (min > ar[i])
                min = ar[i];
        return min;
    }

    void setSales(Sales & s, const double ar[], int n)
    {
        int size = n < QUARTERS ? n : QUARTERS;
        if (size < QUARTERS)
            for (int i = QUARTERS - size; i < QUARTERS; i++)
                s.sales[i] = 0;
        for (int i = 0; i < size; i++)
            s.sales[i] = ar[i];

        s.average = araverage(s.sales, size);
        s.max = armax(s.sales, size);
        s.min = armin(s.sales, size);
    }

    void setSales(Sales & s)
    {
        for (int i = 0; i < QUARTERS; i++)
        {
            cout << "sales #" << i+1 << ": ";
            cin >> s.sales[i];
            cin.get();
        }
        s.average = araverage(s.sales, QUARTERS);
        s.max = armax(s.sales, QUARTERS);
        s.min = armin(s.sales, QUARTERS);
    }

    void showSales(const Sales & s)
    {
        for (int i = 0; i < QUARTERS; i++){
            cout << "Sales #" << i+1 << ": ";
            cout << s.sales[i] << endl;
        }


        cout << "Average: " << s.average << endl;
        cout << "Max Sales: " << s.max << endl;
        cout << "Min Sales: " << s.min << endl;
    }
}
