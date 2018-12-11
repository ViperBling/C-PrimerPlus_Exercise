//
// Created by tuser on 18-12-11.
//

#ifndef STONEWT_H
#define STONEWT_H

class Stonewt {
public:
    enum Mode {STN, INTP, FLOATP};
private:
    Mode mode;
    static const int Lbs_per_stn = 14;
    int stone;          // 英石
    double pds_left;    // 以英石格式显示时，不足一英石的磅数
    double pounds;      // 浮点数磅

public:
    // 分别处理用户输入一个参数，两个参数的情况。
    Stonewt(double lbs, Mode form = STN);
    Stonewt(int stn, double lbs, Mode form = STN);
    Stonewt();
    ~Stonewt();
    void setmode(Mode form);
    // 类型加减乘
    Stonewt operator+(const Stonewt & st) const;
    Stonewt operator-(const Stonewt & st) const;
    Stonewt operator*(const Stonewt & st) const;
    // 数加减乘
    Stonewt operator+(double n) const;
    Stonewt operator-(double n) const;
    Stonewt operator*(double n) const;

    friend Stonewt operator+(double n, const Stonewt & st);
    friend Stonewt operator-(double n, const Stonewt & st);
    friend Stonewt operator*(double n, const Stonewt & st);
    friend std::ostream &operator<<(std::ostream & os, const Stonewt & st);
};

#endif // STONEWT_H
