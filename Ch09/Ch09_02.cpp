#include <iostream>
using namespace std;


void strcount(const string & str);

int main()
{
    string str;

    cout << "Enter a line:\n";
    while (getline(cin, str) and str != ""){
        strcount(str);
        cout << "Enter next line (empty line to quit): \n";
    }

}

void strcount(const string & str)
{
    static int total = 0;
    int count = 0;

    cout << "\"" << str << "\" contains ";
    count = int(str.size());
    total += count;
    cout << count << " characters\n";
    cout << total << " characters total\n";
}