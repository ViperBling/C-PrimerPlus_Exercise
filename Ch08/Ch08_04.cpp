#include <iostream>
#include <cstring>

using namespace std;

struct stringy{
    char * str;
    int ct;
};

void set(stringy & str1, const char * str2);
void show(stringy & str, int n = 1);
void show(const char * str, int n = 1);

int main()
{
    stringy beany;
    char testing[] = "Reality isn't what it used to be: ";
    set(beany, testing);

    show(beany);
    cout << endl;
    show(beany, 2);
    cout << endl;
    testing[0] = 'D';
    testing[1] = 'u';
    show(testing);
    cout << endl;
    show(testing, 3);
    cout << endl;
    show("Done!");
    return 0;
}

void set(stringy & str1, const char * str2)
{
    str1.ct = int(strlen(str2));
    // 分配新的内存空间给字符串
    str1.str = new char[str1.ct + 1];
    strcpy(str1.str, str2);
}

void show(stringy & str, int n)
{
    for (int i = 0; i < n; i++){
        cout << str.str << endl;
    }
}

void show(const char * str, int n)
{
    for (int i = 0; i < n; i++){
        cout << str << endl;
    }
}