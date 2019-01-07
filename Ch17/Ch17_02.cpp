#include <iostream>
#include <fstream>
#include <string>

int main(int argc, char * argv[])
{
    using namespace std;
    string ch;

    if (argc != 2) {
        cout << "Usage: " << argv[0] << " filename[s]\n";
        exit(EXIT_FAILURE);
    }

    ofstream fout(argv[1]);
    if (!fin.is_open()) {
        cerr << "Can't open " << argv[0] << "\n";
        exit(EXIT_FAILURE);
    }
    cout << "Enter your input: \n";
    while (!cin.fail()) {
        getline(cin, ch);
        fout << ch;
    }
    cout << "Done.\n";
    fout.close();
//
//    ifstream fin(argv[1]);
//    cout << "Here are the contents of file: \n";
//    while (fin.get(ch))
//        cout << ch;
//    cout << "\nDone.\n";
//    fin.close();

    return 0;
}