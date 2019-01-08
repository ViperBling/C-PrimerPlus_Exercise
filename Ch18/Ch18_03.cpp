#include <iostream>
using namespace std;

long double sum_value() { return 0;}

template <typename T>
long double sum_value(const T & value) { return value; }

template <typename T, typename... Args>
long double sum_value(const T & value, const Args &... args) {
    return value + sum_value(args...);
}


int main() {
    int n = 24;
    double x = 2.7;
    long y = 2000;
    char ch = 'c';
    cout << "Sum of: " << sum_value(n, x, y, ch) << endl;
    return 0;
}
