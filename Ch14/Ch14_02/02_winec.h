//
// Created by zero on 12/23/18.
//

#ifndef WINE_H
#define WINE_H

#include <string>
#include <valarray>

template <class T1, class T2>
class Pair {
private:
    T1 years;
    T2 bottles;
public:
    Pair(const T1 & yrs, const T2 & bot) : years(yrs), bottles(bot) {}
    Pair() {}
    void Set(const T1 & yr, const T2 & bot);
    T1 & GetYears();
    T2 & GetBotts();
};

typedef std::valarray<int> ArrayInt;
typedef Pair<ArrayInt, ArrayInt> PairArray;

class Wine : private std::string, private PairArray {
private:
    int numyrs;

public:
    Wine(const char * l, int y, const int yr[], const int bot[]);
    Wine(const char * l, int y);
    void GetBottles();
    const std::string & Label();
    int Sum();
    void Show();
};

#endif // WINE_H
