#include <iostream>
#include <array>

using namespace std;

int main()
{
    array<string, 12> mon = {"Jan", "Feb", "Mar",
                             "Apr", "May", "Jun",
                             "Jul", "Aug", "Sep",
                             "Oct", "Nov", "Dec"};
    array<array<int, 12>, 3> sales{};

    int total = 0;

    for (int i = 0; i < 3; i++){
        cout << "Year " << i+1 << endl;
        int sumpery = 0;
        for (int j = 0; j < 12; j++){
            cout << "Year " << i+1 << "\t" <<mon[j] << " sales: ";
            cin >> sales[i][j];
            sumpery += sales[i][j];
        }
        cout << "Year " << i+1 << " sales " << sumpery << "\n\n";
        total += sumpery;
    }
    cout << "Total sales: " << total << endl;

    return 0;
}