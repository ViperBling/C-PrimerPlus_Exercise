#include <iostream>
#include <fstream>
#include <string>

int main(int argc, char * argv[])
{
    using namespace std;
    string str1, str2;

    if (argc != 4) {
        cerr << "Usage: " << argv[0] << " srcfile1 srcfile2 dstfile\n";
        exit(EXIT_FAILURE);
    }
    ifstream fin1(argv[1]);
    ifstream fin2(argv[2]);
    if (!fin1.is_open() || !fin2.is_open()) {
        cerr << "Open source file failed.\n";
        exit(EXIT_FAILURE);
    }
    cout << "Source file 1 contents:\n";
    while (!fin1.eof()) {
        getline(fin1, str1);
        cout << str1 << endl;
    }
    fin1.seekg(0, ios_base::beg);

    cout << "\nSource file 2 contents:\n";
    while (!fin2.eof()) {
        getline(fin2, str2);
        cout << str2 << endl;
    }
    fin2.seekg(0, ios_base::beg);

    ofstream fout(argv[3]);

    while (!fin1.eof() && !fin2.eof()) {
        getline(fin1, str1);
        getline(fin2, str2);
        fout << str1 << " " << str2 << endl;
    }
    while (!fin1.eof()) {
        getline(fin1, str1);
        fout << str1 << endl;
    }
    while (!fin2.eof()) {
        getline(fin2, str2);
        fout << str2 << endl;
    }

    fout.close();
    fin1.close();
    fin2.close();
    cout << "Done.\n";

    return 0;
}
