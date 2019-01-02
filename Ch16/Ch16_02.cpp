#include <iostream>
#include <iterator>
#include <cctype>

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
    std::string tmp1;
    /* 这里有个坑。必须使用const_reverse_iterator来声明p
     * 否则会出现不匹配的情况。原因是st为const类型，p是st的
     * 迭代器，所以也要是const
     */
    std::string::const_reverse_iterator p;
    for (p = st.rbegin(); p != st.rend(); p++) {
        if (isalpha(*p)) {
            tmp1.push_back(tolower(*p));
        }
        else
            continue;
    }
    std::string tmp2(tmp1.rbegin(), tmp1.rend());
    return tmp1 == tmp2;
}