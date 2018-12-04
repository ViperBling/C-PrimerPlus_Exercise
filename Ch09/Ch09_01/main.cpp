#include <iostream>
#include "golf.h"

const int ArSize = 3;

int main()
{
    auto * tmp = new golf[ArSize];
    int i = 0;

    std::cout << "Enter member information: \n";
    while (setgolf(tmp[i]) and ++i < ArSize){
        std::cout << "Enter member information: \n";
    }
    // 如果没有数据录入，退出程序
    if (i == 0){
        std::cout << "No data!\n";
        return 0;
    }
    std::cout << std::endl;

    std::cout << "Show members: \n";
    for (int j = 0; j < ArSize; j++){
        showgolf(tmp[j]);
    }
    std::cout << "Change Handicap: \n";
    for (int j = 0; j < ArSize; j++){
        handicap(tmp[j], j);
        showgolf(tmp[j]);
    }
}