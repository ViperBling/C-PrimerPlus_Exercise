#include <iostream>
#include <string>

using namespace std;

int main()
{
    string input;
    int count = 0;

    cout << "Enter words (to stop, type the word done): \n";
    while (input != "done"){
        cin >> input;
        count++;
    }
    cout << "You entered a total of " << count - 1 << " words.\n";

    return 0;
}