//
// Created by tuser on 18-12-10.
//

#ifndef VECT_H
#define VECT_H

#include <iostream>

namespace VECTOR {
    class Vector {
    public:
        enum Mode {RECT, POL};      // RECT笛卡尔坐标，POL极坐标
    private:
        double x;           // 水平坐标
        double y;           // 垂直坐标
        double mag;         // 极坐标长度
        double ang;         // 极坐标角度
        Mode mode;          // 坐标模式
        void set_mag();
        void set_ang();
        void set_x();
        void set_y();

    public:
        Vector();
        // 自定义构造函数，默认使用笛卡尔坐标系
        Vector(double n1, double n2, Mode form = RECT);
        // 坐标重置方法，将坐标重置回远点
        void reset(double n1, double n2, Mode form = RECT);
        ~Vector();
        double xval() const { return x; }
        double yval() const { return y; }
        double magval() const { return mag; }
        double angval() const { return ang; }
        void polar_mode();      // 设置为极坐标
        void rect_mode();       // 设置为笛卡尔坐标
        // 运算符重载
        Vector operator+(const Vector & b) const;
        Vector operator-(const Vector & b) const;
        // 反转矢量
        Vector operator-() const;
        Vector operator*(double n) const;
        // 友元
        friend Vector operator*(double n, const Vector & a);
        friend std::ostream &operator<<(std::ostream & os, const Vector & v);
    };
}

#endif // VECT_H
