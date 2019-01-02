#include <iostream>

bool palindrome(const std::string & st);

int main()
{
    using std::cout;
    using std::cin;
    using std::string;
    string temp;
    cout << "Enter a word (quit to quit): ";
    while (getline(cin, temp) && temp != "quit") {
        if (palindrome(temp))
            cout << temp << " is palindrome.\n";
        else
            cout << temp << " is not palindrome.\n";
        cout << "Enter a word (quit to quit): ";
    }
    cout << "Done.\n";

    return 0;
}

bool palindrome(const std::string & st) {
    std::string temp(st.rbegin(), st.rend());
    return temp == st;
}