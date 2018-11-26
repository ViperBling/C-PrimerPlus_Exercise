#include <iostream>
#include <array>
#include <string>
#include <vector>

using namespace std;

struct car{
    string make;
    int year;
};

int main()
{
    int num;
    cout << "How many cars do you wish to catalog? ";
    cin >> num;
    cin.get();

    car * list = new car[num];
    for (int i = 0; i < num; i++){
        cout << "Car #" << i+1 << ":\n";
        cout << "Please enter the make: ";
        // string类只能用这种输入方法，别的方法出错。
        getline(cin, list[i].make);
        cout << "Please enter the year made: ";
        cin >> list[i].year;
        // 刷新输入缓冲，避免直接把下个循环开始的提示字符作为输入
        cin.get();
    }
    cout << "Here is your collection:\n";
    for (int i = 0; i < num; i++){
        cout << list[i].year << "\t" << list[i].make << endl;
    }

    delete [] list;

    return 0;
}