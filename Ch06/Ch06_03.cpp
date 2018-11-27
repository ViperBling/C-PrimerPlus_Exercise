#include <iostream>
using namespace std;

const int ArSize = 10;

int main()
{
    char ch;

    cout << "Please enter  one of the following choices: \n";
    cout << "c) carnivore            p) pianist\n";
    cout << "t) tree                 g) game\n";

    while (cin >> ch and ch != 'q'){
        switch (ch) {
            case 'c' : cout << "A maple is a carnivore.\n";
                break;
            case 'p' : cout << "A maple is a pianist.\n";
                break;
            case 't' : cout << "A maple is a tree.\n";
                break;
            case 'g' : cout << "A maple is a game.\n";
                break;
            default : cout << "Please enter a c, p, t, or g: ";
                break;
        }
    }

    return 0;
}
