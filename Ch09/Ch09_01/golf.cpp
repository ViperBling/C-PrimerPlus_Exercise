//
// Created by tuser on 18-12-4.
//
#include <iostream>
#include <cstring>
#include "golf.h"

void setgolf(golf & g, const char * name, int hc)
{
    strcpy(g.fullname, name);
    g.handicap = hc;
}

int setgolf(golf & g)
{
    using namespace std;
    char fulln[Len];
    int handc;
    cout << "Fullname: ";
    cin.get(fulln, Len);
    // 判断是否为空行
    if (cin){
        cout << "Handicap: ";
        cin >> handc;
        cin.get();
        // 使用上一个版本的函数进行结构体赋值
        setgolf(g, fulln, handc);
        return 1;
    }
    else
        return 0;
}


void handicap(golf & g, int hc)
{
    g.handicap = hc;
}

void showgolf(const golf & g)
{
    std::cout << "Fullname: " << g.fullname << std::endl;
    std::cout << "Handicap: " << g.handicap << std::endl;
    std::cout << std::endl;
}