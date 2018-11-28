#include <iostream>
#include <string>
using namespace std;


struct donater{
    string name;
    double money;
};

donater * listInit(int num);

int main()
{
    int num;
    int count = 0;

    cout << "Enter the number of Donator: ";
    cin >> num;
    cin.get();      // 千万别忘了加这一行，如果不把换行符丢弃，
                    // 会在下面函数输入时直接读取换行符，导致第一个Name输入失败。
    donater * list = listInit(num);
    cout << "\n\nGrand Patrons: \n";
    for (int i = 0; i < num; i++){
        if (list[i].money >= 10000){
            cout << list[i].name << " donate $" << list[i].money << endl;
            count++;
        }
    }
    if (count == 0)
        cout << "none\n";

    count = 0;
    cout << "Patrons: \n";
    for (int i = 0; i < num; i++){
        if (list[i].money < 10000){
            cout << list[i].name << " donate $" << list[i].money << endl;
            count++;
        }
    }
    if (count == 0)
        cout << "none\n";
    
    delete [] list;

    return 0;
}

donater * listInit(int num)
{
    auto * namelist = new donater [num];

    for (int i = 0; i < num; i++){
        cout << "Donator #" << i+1 << endl;
        cout << "Name: ";
        getline(cin, namelist[i].name);
        cout << "Money: ";
        cin >> namelist[i].money;
        cin.get();
    }

    return namelist;
}