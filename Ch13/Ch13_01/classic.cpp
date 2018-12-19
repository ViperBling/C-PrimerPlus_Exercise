//
// Created by tuser on 18-12-19.
//
#include "classic.h"
#include <iostream>
#include <cstring>

// 基类
Cd::Cd(const char *s1, const char *s2, int n, double x) {
    strncpy(performers, s1, 49);
    strncpy(label, s2, 19);
    selections = n;
    playtime = x;
}

Cd::Cd(const Cd &d) {
    strcpy(performers, d.performers);
    strcpy(label, d.label);
    selections = d.selections;
    playtime = d.playtime;
}

Cd::~Cd() {}

void Cd::Report() const {
    std::cout << "Performers: " << performers << std::endl;
    std::cout << "Label: " << label << std::endl;
    std::cout << "Selections: " << selections << std::endl;
    std::cout << "Playtime: " << playtime << std::endl;
    std::cout << std::endl;
}

Cd& Cd::operator=(const Cd &d) {
    if (this == &d)
        return *this;
    strcpy(performers, d.performers);
    strcpy(label, d.label);
    selections = d.selections;
    playtime = d.playtime;
    return *this;
}


// 派生类
Classic::Classic(const char *p, const char *s1, const char *s2,
        int n, double x) : Cd(s1, s2, n, x) {
    strncpy(prime, p, 49);
}

Classic::Classic(const Cd &d, const char *p) : Cd(d) {
    strncpy(prime, p, 49);
}

Classic::~Classic() {}

Classic& Classic::operator=(const Classic &cl) {
    if (this == &cl)
        return *this;
    Cd::operator=(cl);
    strcpy(prime, cl.prime);
    return *this;
}

void Classic::Report() const {
    Cd::Report();
    std::cout << "Prime: " << prime << std::endl;
    std::cout << std::endl;
}
