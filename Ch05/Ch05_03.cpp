#include <iostream>
#include <array>

using namespace std;

int main()
{
    int num;
    int sum = 0;

    cout << "Enter a number (0 to quit): ";
    while (cin >> num && num != 0){
        sum += num;
        cout << "Sum = " << sum << endl;
        cout << "Enter a number (0 to quit): ";
    }

    return 0;
}