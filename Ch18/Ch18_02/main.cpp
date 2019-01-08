#include <iostream>
#include "cpmv.h"


int main() {
    {
        using namespace std;
        Cpmv zero, one("one", "one");
        cout << "object zero = ";
        zero.Display();
        cout << "object one = ";
        one.Display();
        Cpmv two = one + one;
        cout << "object two = ";
        two.Display();
        Cpmv three, four;
        cout << "three = one\n";
        three = one;
        cout << "object three = ";
        three.Display();
        cout << "and object one = ";
        one.Display();
        cout << "four = one + two\n";
        four = one + two;
        cout << "object four = ";
        four.Display();
        cout << "four = move(one)\n";
        four = move(one);
        cout << "now object four = ";
        four.Display();
        cout << "and object one = ";
        one.Display();
        return 0;
    }
}
