//
// Created by tuser on 18-12-8.
//

#ifndef STACK_H
#define STACK_H

#include <iostream>

struct customer {
    char fullname[35];
    double payment;
};

typedef customer Item;

class Stack {
private:
    static const int SIZE = 10;
    Item items[SIZE];
    int top;

public:
    Stack();
    bool isempty() const;
    bool isfull() const;
    bool push(const Item & item);
    bool pop(Item & item);
};


#endif // STACK_H
