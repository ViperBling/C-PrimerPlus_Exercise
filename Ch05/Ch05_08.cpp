#include <iostream>
#include <array>
#include <cstring>

using namespace std;


int main()
{
    char *input = new char;
    int count = 0;

    cout << "Enter words (to stop, type the word done): \n";
    while (strcmp(input, "done")){
        cin >> input;
        count++;
    }
    cout << "You entered a total of " << count - 1 << " words.\n";
    delete input;

    return 0;
}