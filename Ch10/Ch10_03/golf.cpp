//
// Created by tuser on 18-12-7.
//

#include <iostream>
#include "golf.h"

Golf::Golf() {
    std::string fulln;
    int handc;
    // 定义静态存储变量记录函数调用次数，也就是生成了几个成员
    static int count = 0;
    std::cout << "Member #" << count+1 << std::endl;
    std::cout << "Fullname: ";
    getline(std::cin, fulln);
    std::cout << "Handicap: ";
    std::cin >> handc;
    std::cin.get();
    *this = Golf(fulln, handc);
    count++;
}

Golf::Golf(const std::string & fname, int handc) {
    fullname = fname;
    handicap = handc;
}

void Golf::hcap(int n) {
    handicap = n;
}

void Golf::showgolf() const {
    std::cout << "Fullname: " << fullname << std::endl;
    std::cout << "Handicap: " << handicap << std::endl;
}