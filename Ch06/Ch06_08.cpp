#include <iostream>
#include <string>
#include <fstream>
using namespace std;


int main()
{
    char ch;
    char filename[30];
    int count = 0;

    ifstream inFile;
    cout << "Enter name of data file: ";
    cin.getline(filename, 30);
    inFile.open(filename);
    if (!inFile.is_open()){
        cout << "Could not open the file " << filename << endl;
        cout << "Program terminating.\n";
        exit(EXIT_FAILURE);
    }
    while (inFile >> ch){
        count++;
    }
    cout << filename << " contains " << count << " characters.\n";
    inFile.close();
    
    return 0;
}