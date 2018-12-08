//
// Created by tuser on 18-12-8.
//

#ifndef PLORG_H
#define PLORG_H

#include <iostream>

class Plorg {
private:
    static const int SIZE = 20;
    char name[SIZE];
    int ci;

public:
    Plorg(const char * ar = "Plorga", int c = 50);
    void setci(int n);
    void showplorg();
};

#endif // PLORG_H
