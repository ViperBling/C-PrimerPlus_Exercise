#include <iostream>
#include "stonewt.h"

const int ArSize = 6;

int main()
{
    using namespace std;
    Stonewt st[ArSize] {Stonewt(11, 0), Stonewt(11, 0), Stonewt(181.2)};
    int stn;
    double pounds, pd_left;
    char ch;
    int i = 2;

    cout << "Enter last 3 element, s for stone type, \n"
            "f for pounds type (q to quit): \n";
    while (cin >> ch && ch != 'q' && ++i < ArSize) {
        if (cin.get() != '\n')
            continue;
        switch (ch) {
            case 'S' :
            case 's' :
                cout << "Enter stone: ";
                cin >> stn;
                cout << "Enter float of stone mode: ";
                cin >> pd_left;
                st[i] = Stonewt(stn, pd_left);
                break;
            case 'F' :
            case 'f' :
                cout << "Enter pounds: ";
                cin >> pounds;
                st[i] = Stonewt(pounds);
                break;
            default:
                break;
        }
        cout << "Enter last 3 element, s for stone type, \n"
                "f for pounds type (q to quit): \n";
    }

    for (int j = 0; j < ArSize; j++)
        cout << "st #" << j+1 << ": " << st[j];
    cout << endl;
    Stonewt Max = st[0];
    Stonewt Min = st[0];
    Stonewt ston1(11, 0);
    int count = 0;
    for (auto const & tmp : st){
        if (Max < tmp)
            Max = tmp;
        if (Min > tmp)
            Min = tmp;
        if (tmp == ston1)
            count++;
    }

    cout << "Max: " << Max;
    cout << "Min: " << Min;
    cout << "Number of weighed equal 11 stone: " << count;


    return 0;
}

