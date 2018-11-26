#include <iostream>

using namespace std;

int main()
{
    int i, j;

    cout << "Enter two number: ";
    cin >> i;
    cin >> j;
    if (i > j){
        int temp;
        temp = i;
        i = j;
        j = temp;
    }
    int sum = i;
    while (i < j){
        sum += ++i;
    }
    cout << sum << endl;

    return 0;
}