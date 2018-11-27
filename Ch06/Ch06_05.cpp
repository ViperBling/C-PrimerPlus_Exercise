#include <iostream>
using namespace std;


int main()
{
    double salary, tax;

    cout << "Please enter your salary: ";
    cin >> salary;

    if (salary <= 5000)
        tax = 0.0;
    else if (salary > 5000 and salary <= 15000)
        tax = (salary - 5000) * 0.10;
    else if (salary > 15000 and salary <= 35000)
        tax = 10000 * 0.1 + (salary - 15000) * 0.15;
    else if (salary > 35000)
        tax = 10000 * 0.1 + 20000 * 0.15 + (salary - 35000) * 0.2;

    cout << "Your tax is: " << tax << endl;

    return 0;
}