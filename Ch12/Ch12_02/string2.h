//
// Created by tuser on 18-12-13.
//

#ifndef STRING2_H
#define STRING2_H

#include <iostream>
using std::ostream;
using std::istream;

class String {
private:
    char * str;
    int len;
    static int num_strings;
    static const int CINLIM = 80;

public:
    String();
    explicit String(const char * s);
    String(const String &);
    ~String();
    int length() const { return len; }

    // 运算符重载
    String &operator=(const String &);
    String &operator=(const char *);
    char &operator[](int i);
    const char &operator[](int i) const;
    String &operator+(const char *);                                             // String s = s + "";
    friend String operator+(const char *, const String & st);                   // String s = "" + s;
    friend String operator+(const String &st1, const String &st2);               // String s = s1 + s2;

    // 重载关系运算符
    friend bool operator<(const String &st1, const String &st2);
    friend bool operator>(const String &st1, const String &st2);
    friend bool operator==(const String &st1, const String &st2);
    friend ostream &operator<<(ostream & os, const String &st);
    friend istream &operator>>(istream & is, String &st);
    static int HowMany();

    // 成员函数
    void stringup();
    void stringlow();
    int has(const char);
};

#endif // STRING2_H
