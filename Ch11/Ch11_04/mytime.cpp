//
// Created by tuser on 18-12-10.
//
#include <iostream>
#include "mytime.h"

Time::Time() {
    hours = minutes = 0;
}

Time::Time(int h, int m) {
    hours = h;
    minutes = m;
}

void Time::AddMin(int m) {
    minutes = m;
    hours += minutes / 60;
    minutes %= 60;
}

void Time::AddHr(int h) {
    hours += h;
}

void Time::Reset(int h, int m) {
    hours = h;
    minutes = m;
}

Time operator+(const Time & t1, const Time & t2) {
    Time sum;
    sum.minutes = t1.minutes + t2.minutes;
    sum.hours = t1.hours + t2.hours + sum.minutes / 60;
    sum.minutes %= 60;
    return sum;
}

Time operator-(const Time & t1, const Time & t2) {
    Time diff;
    int tot1, tot2;
    tot1 = t1.minutes + 60 * t1.hours;
    tot2 = t2.minutes + 60 * t2.hours;
    diff.minutes = (tot1 - tot2) % 60;
    diff.minutes = (tot1 - tot2) / 60;
    return diff;
}

Time operator*(double mult, const Time & t) {
    Time result;
    long totalmin = t.hours * mult * 60 + t.minutes * mult;
    result.hours = totalmin / 60;
    result.minutes = totalmin % 60;
    return result;
}

Time operator*(const Time & t, double n)
{
    return n * t;
}

std::ostream & operator<<(std::ostream & os, const Time & t) {
    os << t.hours << " hours, " << t.minutes << " minutes";
    return os;
}