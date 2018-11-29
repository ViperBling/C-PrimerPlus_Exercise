#include <iostream>
using namespace std;

const int SIZE = 3;

double calculate(double x, double y, double (*pf) (double, double));
double add(double x, double y);
double multi(double x, double y);
double sub(double x, double y);

int main()
{
    double x, y;

    double (*pf[3]) (double, double) = {add, sub, multi};

    cout << "Enter couple of number: ";
    while (cin >> x >> y){
        // range-base loop
        for (double (*f) (double, double) : pf){
            cout << "Result: " << calculate(x, y, f) << endl;
        }
        cout << "Enter couple of number: ";
    }


    return 0;
}

double calculate(double x, double y, double (*pf)(double, double))
{
    return (*pf) (x, y);
}

double add(double x, double y)
{
    return x + y;
}

double multi(double x, double y)
{
    return x * y;
}

double sub(double x, double y)
{
    return x - y;
}