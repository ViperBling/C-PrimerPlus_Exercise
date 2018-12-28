#include <iostream>
#include "tv.h"
using namespace std;


int main()
{
    Tv s42;
    Remote red;
    cout << "Initial settings for 42\" TV:\n";
    s42.settings();
    s42.set_rmode(red, Remote::Regular);
    red.show_remote_mode();
    s42.onoff();
    cout << "\nAdjusted settings for 42\" TV:\n";
    s42.settings();
    s42.set_rmode(red, Remote::Interact);
    red.show_remote_mode();

    return 0;
}
