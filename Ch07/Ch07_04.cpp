#include <iostream>
using namespace std;

long double probability(unsigned numbers, unsigned special, unsigned picks);

int main()
{
    unsigned total, special, choices;
    cout << "Enter the total number of choices on the game card and\n"
            "the number of picks allowed:\n";
    while ((cin >> total >> special >> choices) and choices <= total){
        cout << "You have one chance in ";
        cout << probability(total, special, choices);
        cout << " of winning.\n";
        cout << "Next two numbers (q to quit): ";
    }
    cout << "Bye.\n";

    return 0;
}

long double probability(unsigned numbers, unsigned special, unsigned picks)
{
    long double result = 1.0;
    long double n;
    unsigned p;

    for (n = numbers, p = picks; p > 0; n--, p--)
        result = result * n / p;
    result *= special;
    return result;
}
