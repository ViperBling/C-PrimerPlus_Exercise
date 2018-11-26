#include <iostream>
#include <array>

using namespace std;

int main()
{
    // 两人存款总额
    double Dap, Cle;
    int i = 0;

    Dap = Cle = 100.0;
    while (Cle <= Dap){
        // 复利
        Cle *= 1.05;
        // 单利
        Dap += 10;
        i++;
    }
    cout << "When year = " << i << ", Cleo is richer than Daphne.\n";

    return 0;
}