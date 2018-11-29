#include <iostream>
using namespace std;

const int Seasons = 4;
const char * Snames[Seasons]{"Sping", "Summer", "Fall", "Winter"};

void fill(double arr[], int size);
void show(double arr[]);

int main()
{
    double expenses[Seasons];

    fill(expenses, Seasons);
    show(expenses);

    return 0;
}

void fill(double arr[], int size)
{
    for (int i = 0; i < size; i++){
        cout << "Enter " << Snames[i] << " expenses: ";
        cin >> arr[i];
    }
}

void show(double arr[])
{
    double total = 0.0;

    cout << "\nEXPENSES\n";
    for (int i = 0; i < Seasons; i++){
        cout << Snames[i] << ": $" << arr[i] << endl;
        total += arr[i];
    }
    cout << "Total Expenses: $" << total << endl;
}