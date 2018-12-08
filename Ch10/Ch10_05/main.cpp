#include <iostream>
#include <cstring>
#include "stack.h"

const int ArSize = 35;

int main()
{
    using namespace std;
    Stack st;
    char ch;
    double totoal = 0.0;
    double pay;
    char str[ArSize];

    cout << "Please enter A to add customer,\n"
         << "P to process a PO, or Q to quit.\n";
    while (cin >> ch && toupper(ch) != 'Q'){
        while (cin.get() != '\n')
            continue;
        if (!isalpha(ch)){
            cout << '\a';
            continue;
        }
        switch (ch) {
            case 'A' :
            case 'a' : cout << "Fullname: ";
                       cin.getline(str, ArSize);
                       cout << "Payment: ";
                       cin >> pay;
                       cin.get();
                       Item tmp;
                       strcpy(tmp.fullname, str);
                       tmp.payment = pay;
                       if (st.isfull())
                           cout << "Stack already full\n";
                       else
                           st.push(tmp);
                break;

             case 'P' :
             case 'p' : if (st.isempty())
                            cout << "Stack already empty\n";
                        else{
                            st.pop(tmp);
                            totoal += tmp.payment;
                            cout << "Name: " << tmp.fullname << " popped\n";
                        }
                        cout << "Until now total payment is: " << totoal << endl;
        }
        cout << "Please enter A to add customer,\n"
             << "P to process a PO, or Q to quit.\n";
    }
    cout << "Bye\n";

    return 0;
}