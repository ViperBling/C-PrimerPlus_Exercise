#include <iostream>
using namespace std;

const int strsize = 30;
const int listlen = 3;

struct bop{
    char fullname[strsize];     // real name
    char title[strsize];        // job title
    char bopname[strsize];      // secret BOP name
    int preference;             // 0 = fullname, 1 = title, 2 = bopname
};

bop * listInit(int arsize);

int main()
{
    char ch;
    bop *name = listInit(listlen);

    cout << "\n\nBenevolent Order of Programmer Report\n";
    cout << "a. display by name            b. display by title\n";
    cout << "c. display by bopname         d. display by preference\n";
    cout << "q. quit\n";
    cout << "Enter your choice: ";
    while (cin >> ch and ch != 'q'){
        switch (ch) {
            case 'a' :
                for (int i = 0; i < listlen; i++)
                    cout << name[i].fullname << endl;
                break;
            case 'b' :
                for (int i = 0; i < listlen; i++)
                    cout << name[i].title << endl;
                break;
            case 'c' :
                for (int i = 0; i < listlen; i++)
                    cout << name[i].bopname << endl;
                break;
            case 'd' :
                for (int i = 0; i < listlen; i++){
                    switch (name[i].preference){
                        case 0 : cout << name[i].fullname << endl; break;
                        case 1 : cout << name[i].title << endl; break;
                        case 2 : cout << name[i].bopname << endl; break;
                    }
                }
                break;
            default : cout << "Please enter a a, b, c, or d: ";
                break;
        }
        cout << "Next choice: ";
    }

    delete [] name;
    cout << "Bye!\n";

    return 0;
}

bop * listInit(int arsize)
{
    bop * namelist = new bop[arsize];

    cout << "Please enter programmer information:\n";
    for (int i = 0; i < arsize; i++){
        cout << "Member #" << i+1 << endl;
        cout << "Fullname: ";
        cin.getline(namelist[i].fullname, strsize);
        cout << "Title: ";
        cin.getline(namelist[i].title, strsize);
        cout << "Bopname: ";
        cin.getline(namelist[i].bopname, strsize);
        cout << "Preference: ";
        cin >> namelist[i].preference;
        cin.get();
    }

    return namelist;
}