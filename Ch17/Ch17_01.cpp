#include <iostream>

int main()
{
    using namespace std;
    int ct = 0;
    char ch;
    cout << "Enter: \n";
    while (cin.get(ch) && ch != '$')
        ct++;
    cout << "You entered " << ct << " characters.\n";

    return 0;
}