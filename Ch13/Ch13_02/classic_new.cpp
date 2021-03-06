//
// Created by tuser on 18-12-19.
//
#include "classic.h"
#include <iostream>
#include <cstring>

// 基类
Cd::Cd(const char *s1, const char *s2, int n, double x) {
    performers = new char[strlen(s1) + 1];
    strcpy(performers, s1);
    label = new char[strlen(s2) + 1];
    strcpy(label, s2);
    selections = n;
    playtime = x;
}

Cd::Cd(const Cd &d) {
    performers = new char[strlen(d.performers) + 1];
    label = new char[strlen(d.label) + 1];
    strcpy(performers, d.performers);
    strcpy(label, d.label);
    selections = d.selections;
    playtime = d.playtime;
}

Cd::~Cd() {
    delete [] performers;
    delete [] label;
}

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
    performers = new char[strlen(d.performers) + 1];
    label = new char[strlen(d.label) + 1];
    strcpy(performers, d.performers);
    strcpy(label, d.label);
    selections = d.selections;
    playtime = d.playtime;
    return *this;
}


// 派生类
Classic::Classic(const char *p, const char *s1, const char *s2,
        int n, double x) : Cd(s1, s2, n, x) {
    prime = new char[strlen(p) + 1];
    strcpy(prime, p);
}

Classic::Classic(const Cd &d, const char *p) : Cd(d) {
    prime = new char[strlen(p) + 1];
    strcpy(prime, p);
}

Classic::~Classic() {
    delete [] prime;
}

Classic& Classic::operator=(const Classic &cl) {
    if (this == &cl)
        return *this;
    Cd::operator=(cl);
    prime = new char[strlen(cl.prime) + 1];
    strcpy(prime, cl.prime);
    return *this;
}

void Classic::Report() const {
    Cd::Report();
    std::cout << "Prime: " << prime << std::endl;
    std::cout << std::endl;
}
