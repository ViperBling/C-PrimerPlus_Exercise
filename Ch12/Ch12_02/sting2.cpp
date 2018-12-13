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

String::String(const String & st) {
    len = st.len;
    str = new char[len + 1];
    std::strcpy(str, st.str);
    num_strings++;
}

String::~String() {
    --num_strings;
    delete [] str;
}

String & String::operator=(const String & st) {
    // 检查参数是否为对象本身，是的话什么都不做
    if (this == &st)
        return *this;
    // 清除str之前指向的内存
    delete [] str;
    len = st.len;
    str = new char[len + 1];
    std::strcpy(str, st.str);
    return * this;
}

String & String::operator=(const char * s) {
    delete [] str;
    len = std::strlen(s);
    str = new char[len + 1];
    std::strcpy(str, s);
    return *this;
}

char& String::operator[](int i) {
    return str[i];
}

const char & String::operator[](int i) const {
    return str[i];
}

String & String::operator+(const char * s) {
    len += std::strlen(s);
    char * tmp;
    tmp = new char[len + 1];
    std::strcpy(tmp, str);
    delete [] str;
    std::strcat(tmp, s);
    str = tmp;
    return *this;
}

String operator+(const char *s, const String &st) {
    String t;
    t.len = st.len + std::strlen(s);
    t.str = new char[t.len + 1];
    std::strcpy(t.str, s);
    std::strcat(t.str, st.str);
    return t;
}

String operator+(const String &st1, const String &st2) {
    String s;
    s.len = st1.len + st2.len;
    s.str = new char[s.len + 1];
    std::strcpy(s.str, st1.str);
    std::strcat(s.str, st2.str);
    return s;
}

bool operator<(const String &st1, const String &st2) {
    return (std::strcmp(st1.str, st2.str) < 0);
}

bool operator>(const String &st1, const String &st2) {
    return st2 < st1;
}

bool operator==(const String &st1, const String &st2) {
    return (std::strcmp(st1.str, st2.str) == 0);
}

ostream & operator<<(ostream & os, const String &st) {
    os << st.str;
    return os;
}

istream & operator>>(istream & is, String &st) {
    char temp[String::CINLIM];
    is.get(temp, String::CINLIM);
    if (is)
        st = temp;
    while (is && is.get() != '\n')
        continue;
    return is;
}