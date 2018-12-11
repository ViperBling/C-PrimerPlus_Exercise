//
// Created by tuser on 18-12-11.
//

#ifndef STONEWT_H
#define STONEWT_H

class Stonewt {
public:
    enum Mode {STN, FLTP};
private:
    enum {Lbs_per_stn = 14};
    int stone;
    Mode mode;
    double pds_left;
    double pounds;

public:
    Stonewt(double lbs, Mode form = FLTP);
    Stonewt(int stn, double lbs, Mode form = FLTP);
    Stonewt();
    ~Stonewt();

    void setmode(Mode form);
    bool operator<(const Stonewt & st) const;
    bool operator<=(const Stonewt & st) const;
    bool operator>(const Stonewt & st) const;
    bool operator>=(const Stonewt & st) const;
    bool operator==(const Stonewt & st) const;
    bool operator!=(const Stonewt & st) const;

    friend std::ostream &operator<<(std::ostream & os, const Stonewt & st);
};

#endif // STONEWT_H
