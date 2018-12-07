#include <iostream>
#include "golf.h"

const int ArSize = 3;

int main()
{
    using namespace std;
    Golf * pgolf = new Golf[ArSize];
    cout << endl;
    for (int i = 0; i < ArSize; i++)
        pgolf[i].showgolf();
    cout << endl;
    for (int i = 0; i < ArSize; i++){
        pgolf[i].hcap(i);
        pgolf[i].showgolf();
    }
    
    return 0;
}