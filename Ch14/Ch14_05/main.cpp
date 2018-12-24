#include <iostream>
#include <cstring>
#include "emp.h"
using namespace std;



int main()
{
    employee em("Trip", "Harris", "Thumper");
    cout << em << endl;
    em.ShowAll();
    manager ma("Amorphia", "Spindragon", "Nuancer", 5);
    cout << ma << endl;
    ma.ShowAll();

    fink fi("Matt", "Oggs", "Oiler", "Juno Barr");
    cout << fi << endl;
    fi.ShowAll();
    highfink hf(ma, "Curly Kew");
    hf.ShowAll();
    cout << "Press a key for next phase:\n";
//    cin.get();
    highfink hf2;
    hf2.SetAll();
    cout << endl;

    cout << "Using an abstr_emp * pointer:\n";
    abstr_emp * tri[4] = {&em, &fi, &hf, &hf2};
    for (auto ch : tri){
        ch->ShowAll();
        cout << endl;
    }


    return 0;
}
