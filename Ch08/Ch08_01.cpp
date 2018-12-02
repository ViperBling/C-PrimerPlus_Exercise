#include <iostream>
using namespace std;

void printstr(const char * str, int n = 0);


int main()
{
    char str[20] = "* ";
    printstr(str);
    cout << endl;

    cout << "Now not defualt arguement:\n";

    for (int i = 0; i < 3; i++){
        printstr(str, 1);
        cout << endl;
    }


    return 0;
}

void printstr(const char * str, int n)
{
    static int count = 0;
    count++;
    if (!n)
        cout << str;
    else{
        for (int i = 0; i < count; i++)
            cout << str;
    }
}