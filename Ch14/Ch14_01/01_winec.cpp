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


Wine::Wine(const char *l, int y, const int *yr, const int *bot) {
    label = l;
    numyrs = y;
    pnum.Set(ArrayInt(yr, numyrs), ArrayInt(bot, numyrs));
}

Wine::Wine(const char *l, int y) {
    numyrs = y;
    label = l;
}

void Wine::GetBottles() {
    ArrayInt yr(numyrs), bot(numyrs);
    std::cout << "Enter " << label << " data for " << numyrs << " year(s): \n";
    for (int i = 0; i < numyrs; i++) {
        std::cout << "Enter year: ";
        std::cin >> yr[i];
        std::cout << "Enter bottles for that year: ";
        std::cin >> bot[i];
    }
    pnum.Set(yr, bot);
}

const std::string& Wine::Label() {
    return label;
}

int Wine::Sum() {
    ArrayInt tmp;
    tmp = pnum.GetBotts();
    int sum = 0;
    for (int i = 0; i < numyrs; i++)
        sum += tmp[i];
    return sum;
}

void Wine::Show() {
    std::cout << "Wine: " << label << std::endl;
    std::cout << "\t\tYear\t\tBottles" << std::endl;
    for (int i = 0; i < numyrs; i++)
        std::cout << "\t\t" << pnum.GetYears()[i] << "\t\t" << pnum.GetBotts()[i] << std::endl;
}