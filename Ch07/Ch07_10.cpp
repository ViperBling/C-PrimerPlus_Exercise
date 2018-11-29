#include <iostream>
using namespace std;

const int SIZE = 3;

double calculate(double x, double y, double (*pf[]) (double, double), int n);
double add(double x, double y);
double multi(double x, double y);

int main()
{
    double x, y;

    double * pf[SIZE];
    pf[0] = &add;
    
    cout << "Enter couple of number: ";
    while (cin >> x >> y) {
        cout << "Result: " << calculate(x, y, )
        cout << "Enter couple of number: ";
    }

    return 0;
}

double calculate(double x, double y, double (*pf[])(double, double), int n)
{
    for (int i = 0; i < n; i++){
        return pf[i](x, y);
    }
}

double add(double x, double y)
{
    return x + y;
}

double multi(double x, double y)
{
    return x * y;
}