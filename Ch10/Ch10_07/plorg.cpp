//
// Created by tuser on 18-12-8.
//
#include <iostream>
#include <cstring>
#include "plorg.h"

Plorg::Plorg(const char *ar, int c) {
    strcpy(name, ar);
    ci = c;
}

void Plorg::setci(int n) {
    ci = n;
}

void Plorg::showplorg() {
    std::cout << "Name: " << name << std::endl;
    std::cout << "CI: " << ci << std::endl;
}
