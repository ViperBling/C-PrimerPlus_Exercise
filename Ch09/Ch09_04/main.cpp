#include <iostream>
#include "sales.h"
using namespace std;

int main()
{
    using namespace SALES;

    auto * sale = new Sales[2];
    double ar[QUARTERS] = {130.0, 145.3, 178.1, 187.2};
    setSales(sale[0], ar, 4);
    setSales(sale[1]);

    cout << "Struct Sales 1: \n";
    showSales(sale[0]);
    cout << endl;
    cout << "Struct Sales 2: \n";
    showSales(sale[1]);

    return 0;
}
