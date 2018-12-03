#include <iostream>

using namespace std;

struct CandyBar{
    string name;
    double weight;
    int calorie;
};

void setValue(CandyBar & candy, const char * str="Millennium", double a=2.85, int b=350);
void showCandy(CandyBar & candy);

int main()
{
    CandyBar candy;
    
    cout << "Using defualt arguement:\n";
    setValue(candy);
    showCandy(candy);

    cout << "Set value:\n";
    cout << "Candy Bar name: ";
    getline(cin, candy.name);
    cout << "Candy Bar weight: ";
    cin >> candy.weight;
    cout << "Candy Bar Calorie: ";
    cin >> candy.calorie;
    showCandy(candy);

    return 0;
}

void setValue(CandyBar & candy, const char * str, double a, int b)
{
    candy.name = str;
    candy.weight = a;
    candy.calorie = b;
}

void showCandy(CandyBar & candy)
{
    cout << "Name: " << candy.name << endl;
    cout << "Weight: " << candy.weight << endl;
    cout << "Calorie: " << candy.calorie << endl;
}