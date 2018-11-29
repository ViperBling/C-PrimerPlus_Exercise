#include <iostream>
using namespace std;

long fact(int n);

int main()
{
    long result;
    int n;

    cout << "Fact: ";
    while (cin >> n) {
        result = fact(n);
        cout << "Fact " << n << " is " << result;
        cout << "\nFact: ";
    }

    return 0;
}

long fact(int n)
{
    if (n == 0)
        return 1;
    else
        return n * fact(n - 1);
}
