//
// Created by tuser on 18-12-11.
//

#ifndef COMPLEX0_H
#define COMPLEX0_H

class Complex {
private:
    double real;
    double imag;

public:
    Complex();
    Complex(double r, double i = 0);
    ~Complex();

    Complex operator+(const Complex & c) const;
    Complex operator-(const Complex & c) const;
    Complex operator*(const Complex & c) const;
    Complex operator*(double n) const;
    Complex operator~() const;

    friend Complex operator*(int n, const Complex & c);
    friend std::ostream &operator<<(std::ostream & os, const Complex & c);
    friend std::istream &operator>>(std::istream & os, Complex & c);
};

#endif // COMPLEX0_H
