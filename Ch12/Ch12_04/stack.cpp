//
// Created by tuser on 18-12-14.
//
#include <iostream>
#include "stack.h"

Stack::Stack(int n) {
    size = n;
    top = 0;
    pitems = new Item[n];
}

Stack::Stack(const Stack &st) {
    size = st.size;
    pitems = new Item[size];
//    for (top = 0; top < size; top++)
//        pitems[top] = st.pitems[top];
    top = st.top;
    for (int i = 0; i < size; i++)
        pitems[i] = st.pitems[i];
}

Stack::~Stack() {
    delete [] pitems;
    size = 0;
    top = 0;
}

Stack& Stack::operator=(const Stack &st) {
    if (this == &st)
        return *this;
    delete [] pitems;
    size = st.size;
    pitems = new Item[size];
//    for (top = 0; top < size; top++)
//        pitems[top] = st.pitems[top];
    top = st.top;
    for (int i = 0; i < size; i++)
        pitems[i] = st.pitems[i];

    return *this;
}

bool Stack::isempty() const {
    return top == 0;
}

bool Stack::isfull() const {
    return top == MAX;
}

bool Stack::push(const Item & item) {
    if (top < MAX) {
        pitems[top++] = item;
        return true;
    } else
        return false;
}

bool Stack::pop(Item & item) {
    if (top > 0) {
        item = pitems[--top];
        return true;
    } else
        return false;
}
