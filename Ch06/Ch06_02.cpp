#include <iostream>
using namespace std;

const int ArSize = 10;

int main()
{
    double donation[ArSize];
    int count = 0;
    int i = 0;
    double sum = 0;
    double average;

    cout << "Enter donation value and type non digits to quit: \n";
    cout << "donation #1: ";
    while (i < ArSize and cin >> donation[i]){
        sum += donation[i];
        if (++i < ArSize)
            cout << "donation #" << i+1 << ": ";
    }
    if (i == 0)
        cout << "No data!\n";
    else{
        average = sum / i;
        for (int j = 0; j < i; j++){
            if (donation[j] > average)
                count++;
        }
        cout << "Average: " << average << endl;
        cout << count << " nums lagger than average.\n";
    }

    return 0;
}
