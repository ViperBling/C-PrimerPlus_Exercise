//
// Created by tuser on 18-12-8.
//
#include <iostream>
#include "stack.h"

Stack::Stack() {
    top = 0;
}

bool Stack::isempty() const {
    return top == 0;
}

bool Stack::isfull() const {
    return top == SIZE;
}

bool Stack::push(const Item &item) {
    if (top < SIZE){
        items[top++] = item;
        return true;
    }
    else
        return false;
}

bool Stack::pop(Item &item) {
    if (top > 0){
        item = items[--top];
        return true;
    } else
        return false;
}
