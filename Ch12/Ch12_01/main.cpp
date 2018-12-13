#include <iostream>
#include "cow.h"

int main()
{
    Cow c1;
    Cow c2("Jessie", "sleep hole day", 130.4);
    Cow c3;
    c3 = Cow("Linda", "always eating", 150.5);
    std::cout << "cow1: \n";
    c1.ShowCow();
    std::cout << std::endl;
    c1 = c3;

    std::cout << "cow1 after assign: \n";
    c1.ShowCow();
    std::cout << std::endl;
    std::cout << "cow2:\n";
    c2.ShowCow();
    std::cout << std::endl;
    std::cout << "cow3:\n";
    c3.ShowCow();
    std::cout << std::endl;

    return 0;
}

