#include <iostream>
#include <cctype>
#include <cstring>
#include "workerqe.h"
using namespace std;




int main()
{
    QueueTp<Worker *> wk;
    char ch;
    Worker *add;

    cout << "Enter A to add Worker to queue, P to pop Worker from queue,\n"
         << "S to show queue element and Q to quit: \n";
    while (cin >> ch && toupper(ch) != 'Q') {
        if (toupper(ch) != 'A' && toupper(ch) != 'P' && toupper(ch) != 'S'){
            cout << "Please enter a, p, s, or quit;\n";
            cin >> ch;
        }
        while (cin.get() != '\n')
            continue;
        switch (ch) {

            case 'A' :
            case 'a' :
                cout << "Enter the employee category:\n"
                     << "w: waiter   s: singer   t: singing waiter   q: quit\n";
                char choice;
                cin >> choice;
                while (strchr("wstq", choice) == NULL) {
                    cout << "Please enter a w, s, t, or q: ";
                    cin >> choice;
                }
                cin.get();
                if (choice == 'q')
                    break;
                switch (choice) {
                    case 'w': add = new Waiter;
                        add->Set();
                        break;
                    case 's': add = new Singer;
                        add->Set();
                        break;
                    case 't': add = new SingingWaiter;
                        add->Set();
                        break;
                }

                if (wk.isfull()) {
                    cout << "Queue is full!\n";
                    break;
                } else
                    wk.enqueue(add);
                break;

            case 'P' :
            case 'p' :
                if (wk.isempty()) {
                    cout << "Queue is empty!\n";
                    break;
                } else
                    wk.dequeue(add);
                cout << "Element Popped: \n";
                add->Show();
                cout << endl;
                break;

            case 'S' :
            case 's' :
                if (wk.isempty()) {
                    cout << "Queue is empty!\n";
                    break;
                } else {
                    wk.show();
                }
                break;
        }
        cout << "Enter A to add Worker to queue, P to pop Worker from queue,\n"
             << "S to show queue element and Q to quit: \n";
    }
    cout << "Done\n";

    return 0;
}
