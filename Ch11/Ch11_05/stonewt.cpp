//
// Created by tuser on 18-12-11.
//
#include <iostream>
#include "stonewt.h"

Stonewt::Stonewt(double lbs, Mode form)
{
    stone = int(lbs) / Lbs_per_stn;
    pds_left = int(lbs) % Lbs_per_stn + lbs - int(lbs);
    pounds = lbs;
    mode = form;
}

Stonewt::Stonewt(int stn, double lbs, Mode form)
{
    stone = stn;
    pds_left = lbs;
    pounds = stn * Lbs_per_stn + lbs;
    mode = form;
}

void Stonewt::setmode(Stonewt::Mode form) {
    mode = form;
}

Stonewt::Stonewt() {
    stone = 0;
    pds_left = pounds = 0;
    mode = STN;
}

Stonewt::~Stonewt() {}

Stonewt Stonewt::operator+(const Stonewt &st) const {
    Stonewt sum;
    sum.pounds = pounds + st.pounds;
    sum.stone = int(sum.pounds) / Lbs_per_stn;
    sum.pds_left = int(sum.pounds) % Lbs_per_stn + sum.pounds - int(sum.pounds);
    sum.mode = Stonewt::FLOATP;
    return sum;
}

Stonewt Stonewt::operator+(double n) const {
    Stonewt sum;
    sum.pounds = n + pounds;
    sum.stone = int(sum.pounds) / Lbs_per_stn;
    sum.pds_left = int(sum.pounds) % Lbs_per_stn + sum.pounds - int(sum.pounds);
    sum.mode = Stonewt::FLOATP;
    return sum;
}

Stonewt Stonewt::operator-(const Stonewt &st) const {
    Stonewt diff;
    diff.pounds = pounds - st.pounds;
    diff.stone = int(diff.pounds) / Lbs_per_stn;
    diff.pds_left = int(diff.pounds) % Lbs_per_stn + diff.pounds - int(diff.pounds);
    diff.mode = Stonewt::FLOATP;
    return diff;
}

Stonewt Stonewt::operator-(double n) const {
    Stonewt diff;
    diff.pounds = n - pounds;
    diff.stone = int(diff.pounds) / Lbs_per_stn;
    diff.pds_left = int(diff.pounds) % Lbs_per_stn + diff.pounds - int(diff.pounds);
    diff.mode = Stonewt::FLOATP;
    return diff;
}

Stonewt Stonewt::operator*(const Stonewt &st) const {
    Stonewt mult;
    mult.pounds = pounds * st.pounds;
    mult.stone = int(mult.pounds) / Lbs_per_stn;
    mult.pds_left = int(mult.pounds) % Lbs_per_stn + mult.pounds - int(mult.pounds);
    mult.mode = Stonewt::FLOATP;
    return mult;
}

Stonewt Stonewt::operator*(double n) const {
    Stonewt mult;
    mult.pounds = n * pounds;
    mult.stone = int(mult.pounds) / Lbs_per_stn;
    mult.pds_left = int(mult.pounds) % Lbs_per_stn + mult.pounds - int(mult.pounds);
    mult.mode = Stonewt::FLOATP;
    return mult;
}

Stonewt operator+(double n, const Stonewt & st){
    return st.pounds + n;
}

Stonewt operator-(double n, const Stonewt & st) {
    return st.pounds - n;
}

Stonewt operator*(double n, const Stonewt & st) {
    return st.pounds * n;
}

std::ostream & operator<<(std::ostream & os, const Stonewt & st) {
    if (st.mode == Stonewt::STN)
        os << st.stone << " stone, " << st.pds_left << " pounds\n";
    else if (st.mode == Stonewt::FLOATP)
        os << st.pounds << " pounds\n";
    else if (st.mode == Stonewt::INTP)
        os << int(st.pounds) << " pounds\n";
}