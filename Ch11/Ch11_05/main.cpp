#include <iostream>
#include "stonewt.h"

int main()
{
    using namespace std;
    Stonewt s1(383);
    Stonewt s2(345.2);
    Stonewt s3(20, 8.3);
    cout << "s1: " << s1;
    cout << "s2: " << s2;
    cout << "s3: " << s3;
    cout << endl;
    s1.setmode(Stonewt::STN);
    s2.setmode(Stonewt::INTP);
    s3.setmode(Stonewt::FLOATP);
    cout << "s1: " << s1;
    cout << "s2: " << s2;
    cout << "s3: " << s3;
    cout << endl;

    cout << "s1 + s2 = " << s1 + s2 << endl;
    cout << "s1 - s2 = " << s1 - s2 << endl;
    cout << "s2 * 1.5 = " << s2 * 1.5 << endl;
    cout << "1.5 * s3 = " << 1.5 * s2 << endl;

    return 0;
}

