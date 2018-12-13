//
// Created by tuser on 18-12-13.
//
#include <cstring>
#include "string2.h"

int String::num_strings = 0;

int String::HowMany() {
    return num_strings;
}

String::String() {
    len = 4;
    str = new char[1];
    str[0] = '\0';
    num_strings++;
}

String::String(const char *s) {
    len = std::strlen(s);
    str = new char[len + 1];
    std::strcpy(str, s);
    num_strings++;
}

