#include <iostream>
#include <cstring>
#include "westernshooter.h"
using namespace std;

const int SIZE = 3;

int main()
{
    Person * dude[SIZE];
    int ct;
    for (ct = 0; ct < SIZE; ct++) {
        char choice;
        cout << "Enter Person Category:\n"
             << "g: Guner   p: PokerPlayer   b: BadDude   q: quit\n";
        cin >> choice;
        while (strchr("gpbq", choice) == nullptr) {
            cout << "Please enter a g, p, b, or q: ";
            cin >> choice;
        }
        if (choice == 'q')
            break;
        switch (choice) {
            case 'g':
                dude[ct] = new Gunslmger;
                break;
            case 'p':
                dude[ct] = new PokerPlayer;
                break;
            case 'b':
                dude[ct] = new BadDude;
                break;
            default:
                break;
        }
        cin.get();
        dude[ct]->Set();
    }
    cout << "\nHere is your staff:\n";
    int i = 0;
    for (i = 0; i < ct; i++) {
        cout << endl;
        dude[i]->Show();
    }
    for (i = 0; i < ct; i++)
        delete dude[i];
    cout << "Bye.\n";

    return 0;
}
