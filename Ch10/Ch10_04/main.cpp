#include <iostream>
#include "sales.h"


int main()
{
    double ar[4] = {130.2, 140.1, 152.2, 116.8};

    SALES::Sales Sale1;
    SALES::Sales Sale2(ar, SALES::QUARTERS);
    std::cout << "Object1: \n";
    Sale1.showSales();
    std::cout << std::endl;
    std::cout << "Object2: \n";
    Sale2.showSales();

    return 0;
}