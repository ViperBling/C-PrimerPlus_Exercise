//
// Created by tuser on 18-12-11.
//
#include <iostream>
using std::cout;
#include "stonewt.h"
const double esp = 1e-4;

Stonewt::Stonewt() {
    stone = pounds = pds_left = 0;
    mode = FLTP;
}

Stonewt::Stonewt(double lbs, Mode form) {
    mode = form;
    stone = int(lbs) / Lbs_per_stn;
    pds_left = int(lbs) % Lbs_per_stn + lbs - int(lbs);
    pounds = lbs;
}

Stonewt::Stonewt(int stn, double lbs, Mode form) {
    mode = form;
    stone = stn;
    pds_left = lbs;
    pounds = stn * Lbs_per_stn + lbs;
}

Stonewt::~Stonewt() {}

bool Stonewt::operator<(const Stonewt &st) const {
    return pounds < st.pounds;
}

void Stonewt::setmode(Stonewt::Mode form) {
    mode = form;
}

bool Stonewt::operator<=(const Stonewt &st) const {
    double x = pounds - st.pounds;
    if (pounds < st.pounds)
        return true;
    else
        return x <= esp && x >= -esp;
}

bool Stonewt::operator>(const Stonewt &st) const {
    return pounds > st.pounds;
}

bool Stonewt::operator>=(const Stonewt &st) const {
    double x = pounds - st.pounds;
    if (pounds > st.pounds)
        return true;
    else
        return x <= esp && x >= -esp;
}

bool Stonewt::operator==(const Stonewt &st) const {
    double x = pounds - st.pounds;
    return x <= esp && x >= -esp;
}

bool Stonewt::operator!=(const Stonewt &st) const {
    double x = pounds - st.pounds;
    return x >= esp && x <= -esp;
}

std::ostream & operator<<(std::ostream & os, const Stonewt & st) {
    if (st.mode == Stonewt::STN)
        os << st.stone << " stone, " << st.pounds << " pounds\n";
    else if (st.mode == Stonewt::FLTP)
        os << st.pounds << " pounds\n";
    else
        os << "Incorrect mode.\n";
}
