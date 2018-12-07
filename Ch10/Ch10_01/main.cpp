#include <iostream>
#include "bank.h"

int main()
{
    using namespace std;
    Bankac Jack;
    string name, account;
    double balance;
    char ch;

    cout << "Enter your information (a to continue, q to quit): \n";

    while (cin.get(ch) and ch != 'q'){
        while (cin.get() != '\n')
            continue;
        cout << "Name: ";
        getline(cin, name);
        cout << "Account: ";
        getline(cin, account);
        cout << "Balance: ";
        cin >> balance;
        Jack = Bankac(name, account, balance);
        Jack.show();

        double depos;
        cout << "Enter the deposit: ";
        cin >> depos;
        Jack.deposit(depos);
        Jack.show();

        double withdraw;
        cout << "Enter the withdraw: ";
        cin >> withdraw;
        Jack.withdraw(withdraw);
        Jack.show();

        cout << "Enter your information (q to quit): \n";
    }

    return 0;
}