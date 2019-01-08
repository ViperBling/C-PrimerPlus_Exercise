//
// Created by tuser on 19-1-8.
//

#include "cpmv.h"
#include <iostream>

Cpmv::Cpmv() {
    pi = new Info;
    pi->qcode = "None";
    pi->zcode = "None";
    std::cout << "Default constructor called.\n";
    Display();
}

Cpmv::Cpmv(std::string q, std::string z) {
    pi = new Info;
    pi->qcode = q;
    pi->zcode = z;
    std::cout << "String constructor called.\n";
    Display();
}

Cpmv::Cpmv(const Cpmv & cp) {
    pi = new Info;
    std::cout << "Copy constructor called.\n";
    pi->qcode = cp.pi->qcode;
    pi->zcode = cp.pi->zcode;
    Display();
}

Cpmv::Cpmv(Cpmv && mv) {
    std::cout << "Move constructor called.\n";
    pi = new Info;
    pi->qcode = mv.pi->qcode;
    pi->zcode = mv.pi->zcode;
    mv.pi->qcode = "None";
    mv.pi->zcode = "None";
}

Cpmv::~Cpmv() {
    std::cout << "Destructor called.\n";
    delete pi;
}

Cpmv& Cpmv::operator=(const Cpmv &cp) {
    std::cout << "Copy assignment operator called.\n";
    if (this == &cp)
        return *this;
    pi->qcode = cp.pi->qcode;
    pi->zcode = cp.pi->zcode;
    Display();
    return *this;
}

Cpmv& Cpmv::operator=(Cpmv &&mv) {
    std::cout << "Move assignment operator called.\n";
    if (this == &mv)
        return *this;
    pi->qcode = mv.pi->qcode;
    pi->zcode = mv.pi->zcode;
    mv.pi->qcode = "None";
    mv.pi->zcode = "None";
    Display();
    return *this;
}

Cpmv Cpmv::operator+(const Cpmv &obj) const {
    std::cout << "Plus assignment operator called.\n";
    this->pi->qcode += obj.pi->qcode;
    this->pi->zcode += obj.pi->zcode;
    return *this;
}

void Cpmv::Display() const {
    std::cout << pi->qcode << ", " << pi->zcode << std::endl;
}