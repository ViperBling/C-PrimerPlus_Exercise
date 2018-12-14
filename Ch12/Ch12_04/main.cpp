#include <iostream>
#include <cctype>
#include "stack.h"


int main()
{
    using namespace std;
    Stack st;
    cout << "Init stack1: \n";
    cout << "Is stack1 empty: " << st.isempty() << endl;
    cout << "Is stack1 full: " << st.isfull() << endl;
    cout << endl;
    cout << "Push 10 item to stack1: \n";
    Item item[10];
    for (int i = 0; i < 10; i++) {
        item[i] = i + 1;
        st.push(item[i]);
    }
    cout << "Is stack1 full: " << st.isfull() << endl;
    cout << endl;

    cout << "Init stack2: \n";
    Stack po;
    po = st;
    cout << "Is stack2 empty: " << po.isempty() << endl;

    cout << "Is stack2 full: " << po.isfull() << endl;
    cout << endl;

    Item item1[10] {};
    cout << "New array item1: \n";
    for (auto it : item1)
        cout << it << " ";
    cout << "\nPop stack2 to item1: \n";
    for (auto it : item1) {
        po.pop(it);
        cout << it << " ";
    }

    return 0;
}

