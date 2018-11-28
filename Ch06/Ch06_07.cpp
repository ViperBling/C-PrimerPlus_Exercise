#include <iostream>
#include <string>
#include <cctype>
using namespace std;


int main()
{
    string str;
    int vowels, conson, others;

    vowels = conson = others = 0;
    cout << "Enter words (q to quit):\n";
    while (cin >> str and str != "q"){
        if (isalpha(str[0])){
            switch (str[0]){
                case 'A':
                case 'a':
                case 'E':
                case 'e':
                case 'I':
                case 'i':
                case 'O':
                case 'o':
                case 'U':
                case 'u': vowels++;
                    break;
                default: conson++;
                    break;
            }
        }
        else
            others++;
    }
    cout << vowels << " words beginning with vowels\n";
    cout << conson << " words beginning with consonants\n";
    cout << others << " others\n";

    return 0;
}