//
// Created by tuser on 18-12-14.
//

#ifndef STACK_H
#define STACK_H

typedef unsigned long Item;

class Stack {
    Item * pitems;
    int size;
    int top;
    static const int MAX = 10;

public:
    Stack(int n = MAX);
    Stack(const Stack & st);
    ~Stack();
    Stack &operator=(const Stack & st);
    bool isempty() const;
    bool isfull() const;
    bool push(const Item & item);
    bool pop(Item & item);
};

#endif // STACK_H
