#include <iostream>
#include <cctype>

using namespace std;

void upper(string & str);

int main()
{
    string str;

    cout << "Enter a string (q to quit): ";
    while (getline(cin, str) and str != "q"){
        upper(str);
        cout << str << endl;
        cout << "Next string (q to quit): ";
    }
    cout << "Bye.\n";

    return 0;
}

void upper(string & str)
{
    for (int i = 0; i < str.length(); i++)
        str[i] = toupper(str[i]);
}