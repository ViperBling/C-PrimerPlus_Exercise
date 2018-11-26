#include <iostream>

using namespace std;

int main()
{
    int lines;
    cout << "Enter number of rows: ";
    cin >> lines;

    for (int i = 0; i < lines; i++){
        for (int j = 1; j < lines - i; j++)
            cout << '.';
        for (int k = 0; k < i+1; k++)
            cout << '*';
        cout << "\n";
    }

    return 0;
}