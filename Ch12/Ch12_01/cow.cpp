//
// Created by tuser on 18-12-13.
//
#include <iostream>
#include <cstring>
#include "cow.h"

Cow::Cow() {
    name[0] = '\0';
    hobby = new char[1];
    hobby[0] = '\0';
    weight = 0.0;
}

Cow::Cow(const char *nm, const char *ho, double wt) {
    strcpy(name, nm);
    size_t len = strlen(ho);
    hobby = new char[len + 1];
    strcpy(hobby, ho);
    weight = wt;
}

Cow::Cow(const Cow &c) {
    strcpy(name, c.name);
    size_t len = strlen(c.hobby);
    hobby = new char[len + 1];
    strcpy(hobby, c.hobby);
    weight = c.weight;
}

Cow& Cow::operator=(const Cow &c) {
    size_t len = strlen(c.hobby);
    if (this == &c)
        return * this;
    delete [] hobby;
    weight = c.weight;
    hobby = new char[len + 1];
    strcpy(name, c.name);
    strcpy(hobby, c.hobby);
    return * this;
}

Cow::~Cow() {
    delete [] hobby;
}

void Cow::ShowCow() const {
    std::cout << "Cow name: " << name << std::endl;
    std::cout << "Cow hobby: " << hobby << std::endl;
    std::cout << "Cow weight: " << weight << std::endl;
}