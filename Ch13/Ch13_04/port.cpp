//
// Created by tuser on 18-12-19.
//
#include <iostream>
#include <cstring>
#include "port.h"

Port::Port(const char *br, const char *st, int b) {
    brand = new char[strlen(br) + 1];
    strcpy(brand, br);
    strncpy(style, st, 20);
    bottles = b;
}

Port::Port(const Port &p) {
    brand = new char[strlen(p.brand) + 1];
    strcpy(brand, p.brand);
    strncpy(style, p.style, 20);
    bottles = p.bottles;
}

Port& Port::operator=(const Port &p) {
    if (this == &p)
        return *this;
    delete [] brand;
    brand = new char[strlen(p.brand) + 1];
    strcpy(brand, p.brand);
    strncpy(style, p.style, 20);
    bottles = p.bottles;
    return *this;
}

Port& Port::operator+=(int b) {
    bottles += b;
    return *this;
}

Port& Port::operator-=(int b) {
    if (bottles < b)
        cout << "Not enough bottles!\n";
    else
        bottles -= b;
    return *this;
}

void Port::Show() const {
    cout << "Brand: " << brand << endl;
    cout << "Kind: " << style << endl;
    cout << "Bottles: " << bottles << endl;
}

ostream &operator<<(ostream &os, const Port &p) {
    os << p.brand << ", " << p.style << ", " << p.bottles << endl;
    return os;
}


// VintagePort
VintagePort::VintagePort() : Port() {
    nickname = new char[4];
    strcpy(nickname, "null");
    year = 0;
}

VintagePort::VintagePort(const char *br, int b,
        const char *nn, int y) : Port(br, "vintage", b) {
    nickname = new char[strlen(nn) + 1];
    strcpy(nickname, nn);
    year = y;
}

VintagePort::VintagePort(const VintagePort &vp) : Port(vp){
    nickname = new char[strlen(vp.nickname) + 1];
    strcpy(nickname, vp.nickname);
    year = vp.year;
}

VintagePort& VintagePort::operator=(const VintagePort &vp) {
    if (this == &vp)
        return *this;
    delete [] nickname;
    Port::operator=(vp);
    nickname = new char[strlen(vp.nickname) + 1];
    strcpy(nickname, vp.nickname);
    year = vp.year;
    return *this;
}

void VintagePort::Show() const {
    Port::Show();
    cout << "NickName: " << nickname << endl;
    cout << "Year: " << year << endl;
}

ostream &operator<<(ostream & os, const VintagePort &vp) {
    os << (const Port &) vp;
    os << vp.nickname << ", " << vp.year << endl;
    return os;
}