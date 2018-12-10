//
// Created by tuser on 18-12-10.
//
#include <cmath>
#include "vect.h"
using namespace std;


namespace VECTOR {
    // 从弧度制转换成角度制
    const double Rad_to_degree = 45.0 / atan(1.0);
    // 上面的结果是约为57.3，就是1弧度等于的角度值

    // private methods
    // 计算极坐标
    double Vector::set_mag() {
        double mag;
        mag = sqrt(x * x + y * y);
        return mag;
    }
    double Vector::set_ang() {
        double ang;
        if (x == 0.0 && y == 0.0)
            ang = 0.0;
        else
            ang = atan2(y, x);
        return ang;
    }

    // 计算直角坐标
    void Vector::set_x(double mag, double ang) {
        x = mag * cos(ang);
    }
    void Vector::set_y(double mag, double ang) {
        y = mag * sin(ang);
    }

    // public methods
    Vector::Vector() {
        x = y = 0.0;
        mode = RECT;
    }
    // 自定义构造函数。如果坐标形式是直角坐标，那么同时设定极坐标
    // 如果坐标形式是极坐标，那么同时设定直角坐标
    Vector::Vector(double n1, double n2, VECTOR::Vector::Mode form) {
        mode = form;
        if (mode == RECT){
            x = n1;
            y = n2;
            set_mag();
            set_ang();
        } else if (mode == POL) {
            double mag, ang;
            mag = n1;
            ang = n2 / Rad_to_degree;
            set_x(mag, ang);
            set_y(mag, ang);
        } else {
            cout << "Incorrect 3rd argument to Vector() -- ";
            cout << "vector set to 0\n";
            x = y = 0.0;
            mode = RECT;
        }
    }
    // 重置坐标
    void Vector::reset(double n1, double n2, VECTOR::Vector::Mode form) {
        mode = form;
        if (mode == RECT){
            x = n1;
            y = n2;
            set_mag();
            set_ang();
        } else if (mode == POL) {
            double mag, ang;
            mag = n1;
            ang = n2 / Rad_to_degree;
            set_x(mag, ang);
            set_y(mag, ang);
        } else {
            cout << "Incorrect 3rd argument to Vector() -- ";
            cout << "vector set to 0\n";
            x = y = 0.0;
            mode = RECT;
        }
    }

    Vector::~Vector() {}

    void Vector::polar_mode() {
        mode = POL;
    }
    void Vector::rect_mode() {
        mode = RECT;
    }

    // 运算符重载，直接使用构造函数进行重载
    Vector Vector::operator+(const VECTOR::Vector &b) const {
        return Vector(x + b.x, y + b.y);
    }
    Vector Vector::operator-(const VECTOR::Vector &b) const {
        return Vector(x - b.x, y - b.y);
    }
    Vector Vector::operator-() const {
        return Vector(-x, -y);
    }
    Vector Vector::operator*(double n) const {
        return Vector(n * x, n * y);
    }

    // 友元
    Vector operator*(double n, const Vector & a) {
        return a * n;
    }
    std::ostream & operator<<(std::ostream & os, const Vector & v) {
        if (v.mode == Vector::RECT)
            os << "(x, y) = (" << v.x << ", " << v.y << ")";
        else if (v.mode == Vector::POL)
            os << "(m, a) = (" << v.magval() << ", " << v.angval() << ")";
        else
            os << "Vector object mode is invalid";
        return os;
    }
} // end namespace VECTOR
