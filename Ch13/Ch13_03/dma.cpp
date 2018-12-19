//
// Created by tuser on 18-12-18.
//
#include <cstring>
#include "dma.h"

// abcDMA
abcDMA::abcDMA(const char *l, int r) {
    label = new char[strlen(l) + 1];
    strcpy(label, l);
    rating = r;
}

abcDMA::abcDMA(const abcDMA &ad) {
    label = new char[strlen(ad.label) + 1];
    strcpy(label, ad.label);
    rating = ad.rating;
}

abcDMA::~abcDMA() {
    delete [] label;
}

abcDMA& abcDMA::operator=(const abcDMA &ad) {
    if (this == &ad)
        return *this;
    delete [] label;
    label = new char[strlen(ad.label) + 1];
    strcpy(label, ad.label);
    rating = ad.rating;
    return *this;
}

void abcDMA::View() {
    std::cout << "Label: " << label << std::endl;
    std::cout << "Rating: " << rating << std::endl;
}

std::ostream &operator<<(std::ostream &os, const abcDMA &ad) {
    os << "Label: " << ad.label << std::endl;
    os << "Rating: " << ad.rating << std::endl;
    return os;
}


// baseDMA
baseDMA::baseDMA(const char *l, int r) : abcDMA(l, r) {}

baseDMA::baseDMA(const abcDMA &ad) : abcDMA(ad) {}

void baseDMA::View() {
    abcDMA::View();
}


// lacksDMA
lacksDMA::lacksDMA(const char *c, const char *l, int r) : abcDMA(l, r) {
    strncpy(color, c, COL_LEN - 1);
}

lacksDMA::lacksDMA(const char * c, const abcDMA & ad) : abcDMA(ad) {
    strncpy(color, c, COL_LEN - 1);
}

lacksDMA::lacksDMA(const lacksDMA &ls) : abcDMA(ls) {
    strncpy(color, ls.color, COL_LEN - 1);
}

void lacksDMA::View() {
    abcDMA::View();
    std::cout << "Color: " << color << std::endl;
}

std::ostream &operator<<(std::ostream &os, const lacksDMA &ls) {
    os << (const abcDMA &) ls;
    os << "Color: " << ls.color << std::endl;
    return os;
}


// hasDMA
hasDMA::hasDMA(const char *s, const char *l, int r) : abcDMA(l, r) {
    style = new char[strlen(s) + 1];
    strcpy(style, s);
}

hasDMA::hasDMA(const char *s, const abcDMA &ad) : abcDMA(ad) {
    style = new char[strlen(s) + 1];
    strcpy(style, s);
}

hasDMA::hasDMA(const hasDMA &hs) : abcDMA(hs) {
    style = new char[strlen(hs.style) + 1];
    strcpy(style, hs.style);
}

hasDMA::~hasDMA() {
    delete [] style;
}

hasDMA& hasDMA::operator=(const hasDMA &hs) {
    if (this == &hs)
        return *this;
    delete [] style;
    abcDMA::operator=(hs);
    style = new char[strlen(hs.style) + 1];
    strcpy(style, hs.style);
    return *this;
}

void hasDMA::View() {
    abcDMA::View();
    std::cout << "Style: " << style << std::endl;
}

std::ostream &operator<<(std::ostream &os, const hasDMA &hs) {
    os << (const abcDMA &) hs;
    os << "Style: " << hs.style << std::endl;
    return os;
}

