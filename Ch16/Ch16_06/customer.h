//
// Created by tuser on 19-1-2.
//

#ifndef CUSTOMER_H
#define CUSTOMER_H

#include <iostream>

class Customer {
private:
    long arrive;
    int processtime;
public:
    Customer() { arrive = processtime = 0; }
    void set(long when) { processtime = std::rand() % 3 + 1; arrive = when; }
    long when() const { return arrive; }
    int ptime() const { return processtime; }
};

#endif // CUSTOMER_H
