#include <iostream>
#include "list.h"

int main()
{
    using namespace std;
    List tmp;
    Item elem;
    char ch;

    cout << "Enter A to add a element of list, \n"
         << "S to show the list, Q to quit.\n";
    while (cin >> ch && toupper(ch) != 'Q') {
        while (cin.get() != '\n')
            continue;
        if (!isalpha(ch))
            continue;
        switch (ch) {
            case 'A' :
            case 'a' :  cout << "Enter a number: ";
                        cin >> elem;
                        if (tmp.isfull())
                            cout << "List is full.\n";
                        else
                            tmp.add(elem);
                break;
            case 'S' :
            case 's' :  if (tmp.isempty())
                            cout << "List is empty.\n";
                        else
                            tmp.traverse(show);
                break;
        }
        cout << "Enter A to add a element of list, \n"
             << "S to show the list, Q to quit.\n";
    }
    cout << "Bye.\n";

    return 0;
}