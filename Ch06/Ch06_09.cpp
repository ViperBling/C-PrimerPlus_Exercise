#include <iostream>
#include <fstream>
#include <string>
using namespace std;


struct donater{
    string name;
    double money;
};

int main()
{
    int num;
    int count = 0;
    string filename;
    int i = 0;

    ifstream inFile;
    cout << "Please enter filename of patrons: ";
    getline(cin, filename);
    inFile.open(filename);
    if (!inFile.is_open()){
        cout << "Could not open the file " << filename << endl;
        cout << "Terminating.\n";
        exit(EXIT_FAILURE);
    }
    (inFile >> num).get();      // 注意这里要加get(), 不是cin.get(), 因为这是文件IO
    auto * list = new donater [num];

    while (inFile.good() and i < num){      // 设置标志，EOF时退出循环
        getline(inFile, list[i].name);
        (inFile >> list[i].money).get();
        i++;
    }

    cout << "\n\nGrand Patrons: \n";
    for (int j = 0; j < num; j++){
        if (list[j].money >= 10000){
            cout << list[j].name << " donate $" << list[j].money << endl;
            count++;
        }
    }
    if (count == 0)
        cout << "none\n";

    count = 0;
    cout << "\nPatrons: \n";
    for (int j = 0; j < num; j++){
        if (list[j].money < 10000){
            cout << list[j].name << " donate $" << list[j].money << endl;
            count++;
        }
    }
    if (count == 0)
        cout << "none\n";

    delete [] list;

    return 0;
}