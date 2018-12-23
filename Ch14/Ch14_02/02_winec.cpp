//
// Created by zero on 12/23/18.
//
#include <iostream>
#include "winec.h"

template <class T1, class T2>
void Pair<T1, T2>::Set(const T1 & yrs, const T2 & bot) {
    years = yrs;
    bottles = bot;
}

template <class T1, class T2>
T1 & Pair<T1, T2>::GetYears() {
    return years;
}

template <class T1, class T2>
T2 & Pair<T1, T2>::GetBotts() {
    return bottles;
}


Wine::Wine(const char *l, int y, const int *yr, const int *bot)
        : std::string(l), numyrs(y), PairArray(ArrayInt(yr, y), ArrayInt(bot, y)) {}

Wine::Wine(const char *l, int y) : std::string(l), numyrs(y) {}

void Wine::GetBottles() {
    ArrayInt yr(numyrs), bot(numyrs);
    std::cout << "Enter " << (const std::string &) *this << " data for " << numyrs << " year(s): \n";
    for (int i = 0; i < numyrs; i++) {
        std::cout << "Enter year: ";
        std::cin >> yr[i];
        std::cout << "Enter bottles for that year: ";
        std::cin >> bot[i];
    }
    PairArray::Set(yr, bot);
}

const std::string& Wine::Label() {
    return (const std::string &) *this;         // 强制转换为string类型，就可以输出label
}

int Wine::Sum() {
    ArrayInt tmp;
    tmp = PairArray::GetBotts();
    int sum = 0;
    for (int i = 0; i < numyrs; i++)
        sum += tmp[i];
    return sum;
}

void Wine::Show() {
    std::cout << "Wine: " << (const std::string &) *this << std::endl;
    std::cout << "\t\tYear\t\tBottles" << std::endl;
    for (int i = 0; i < numyrs; i++)
        std::cout << "\t\t" << PairArray::GetYears()[i] << "\t\t" << PairArray::GetBotts()[i] << std::endl;
}