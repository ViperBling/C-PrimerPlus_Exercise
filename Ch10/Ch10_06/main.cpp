#include <iostream>
#include "move.h"

int main()
{
    using namespace std;
    Move a(4.3, 1.2);
    Move b(1.2, 2.3);
    cout << "Point a: \n";
    a.showmove();
    cout << "Point b: \n";
    b.showmove();

    Move c = a.add(b);
    cout << "Vector a add vector b: \n";
    c.showmove();
    cout << endl;

    cout << "Reset c: \n";
    c.reset();
    c.showmove();

    return 0;
}