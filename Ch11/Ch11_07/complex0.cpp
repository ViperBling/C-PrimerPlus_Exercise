//
// Created by tuser on 18-12-11.
//
#include <iostream>
#include "complex0.h"

Complex::Complex() {
    real = imag = 0.0;
}

Complex::Complex(double r, double i) {
    real = r;
    imag = i;
}

Complex::~Complex() {}

// 使用构造函数来重载
Complex Complex::operator+(const Complex &c) const {
    return Complex(real + c.real, imag + c.imag);
}

Complex Complex::operator-(const Complex &c) const {
    return Complex(real - c.real, imag - c.imag);
}

Complex Complex::operator*(const Complex &c) const {
    Complex tmp;
    tmp.real = real * c.real - imag * c.imag;
    tmp.imag = real * c.imag + imag * c.real;
    return tmp;
}

Complex Complex::operator*(double n) const {
    return Complex(n*real, n*imag);
}

Complex Complex::operator~() const {
    return Complex(real, -imag);
}

Complex operator*(int n, const Complex & c) {
    return Complex(n * c.real, n * c.imag);
}

std::ostream &operator<<(std::ostream & os, const Complex & c)
{
    os << "(" << c.real << ", " << c.imag << "i)";
    return os;
}

std::istream &operator>>(std::istream & is, Complex & c)
{
    std::cout << "real: ";
    if (is >> c.real) {     // 这里加入判断，避免输入q之后继续输出imaginary.
        std::cout << "imaginary: ";
        is >> c.imag;
    }
    return is;
}