#include <iostream>
#include <array>

using namespace std;

int main()
{
    array<string, 12> mon = {"Jan", "Feb", "Mar",
                             "Apr", "May", "Jun", 
                             "Jul", "Aug", "Sep", 
                             "Oct", "Nov", "Dec"};
    array<int, 12> sales{};
    int sum = 0;

    for (int i = 1; i < 13; i++){
        cout << mon[i - 1] << " sales: ";
        cin >> sales[i - 1];
        sum += sales[i - 1];
    }
    cout << "\n\nYears total sales: " << sum << endl;

    return 0;
}