#include <iostream>
#include <cctype>
using namespace std;

int main()
{
    char ch;

    cout << "Enter text and type @ to terminate.\n";

    while (cin.get(ch) and ch != '@'){
        if (!isdigit(ch)){
            if (isalpha(ch)){
                if (isupper(ch)) {
                    ch = tolower(ch);
                }
                else if (islower(ch)){
                    ch = toupper(ch);
                }
            }
            cout << ch;
        }
    }

    return 0;
}
