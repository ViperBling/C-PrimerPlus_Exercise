#include <iostream>
#include "plorg.h"

const int LEN = 20;

int main()
{
    using namespace std;
    char name[LEN];
    int cit;
    Plorg pl;
    cout << "Default Plorg: \n";
    pl.showplorg();

    cout << "Enter Plorg name: ";
    cin.getline(name, LEN);
    cout << "Enter CI: ";
    cin >> cit;
    cin.get();
    pl = Plorg(name, cit);
    pl.showplorg();

    cout << "Enter a new ci: ";
    cin >> cit;
    pl.setci(cit);
    pl.showplorg();

    return 0;
}