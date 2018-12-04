//
// Created by tuser on 18-12-4.
//
#ifndef GOLF_H
#define GOLF_H

const int Len = 40;
struct golf{
    char fullname[Len];
    int handicap;
};

void setgolf(golf & g, const char * name, int hc);

int setgolf(golf & g);

void handicap(golf & g, int hc);

void showgolf(const golf & g);

#endif //C_PRIMER_GOLF_H

