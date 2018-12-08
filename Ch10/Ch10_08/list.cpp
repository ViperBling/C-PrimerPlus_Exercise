//
// Created by tuser on 18-12-8.
//
#include <iostream>
#include "list.h"

List::List() {
    tail = 0;
}

bool List::add(Item & item)
{
    if (tail < MAX){
        items[tail++] = item;
        return true;
    } else
        return false;
}

void List::traverse(void (*pf)(Item &))
{
    for (int i = 0; i < tail; i++)
        pf(items[i]);
}

bool List::isempty() const
{
    return tail == 0;
}

bool List::isfull() const
{
    return tail == MAX;
}

void show(Item & item)
{
    std::cout << item << std::endl;
}