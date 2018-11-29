#include <iostream>
using namespace std;

const int Seasons = 4;
const char * Snames[Seasons]{"Sping", "Summer", "Fall", "Winter"};

struct expense{
    double expe[Seasons];
};

void fill(expense * arr);
void show(expense arr);

int main()
{
    expense a;

    fill(&a);
    show(a);

    return 0;
}

void fill(expense * arr)
{
    for (int i = 0; i < Seasons; i++){
        cout << "Enter " << Snames[i] << " expenses: ";
        cin >> arr->expe[i];
    }
}

void show(expense arr)
{
    double total = 0.0;

    cout << "\nEXPENSES\n";
    for (int i = 0; i < Seasons; i++){
        cout << Snames[i] << ": $" << arr.expe[i] << endl;
        total += arr.expe[i];
    }
    cout << "Total Expenses: $" << total << endl;
}