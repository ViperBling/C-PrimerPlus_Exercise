#include <iostream>
using namespace std;

double harmean(double x, double y);

int main()
{
    double x, y;
    double result;

    cout << "Enter two number (not 0) : ";
    while (cin >> x >> y and x*y != 0){
        result = harmean(x, y);
        cout << "Harmonic mean: " << result;
        cout << "\nEnter two number (not 0) : ";
    }
    cout << "Bye.\n";

    return 0;
}

double harmean(double x, double y)
{
    return 2.0 * x * y / (x + y);
}