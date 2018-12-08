//
// Created by tuser on 18-12-8.
//
#include <iostream>
#include "move.h"

Move::Move(double a, double b)
{
    x = a;
    y = b;
}

void Move::showmove() const
{
    std::cout << "x axis: " << x << std::endl;
    std::cout << "y axis: " << y << std::endl;
}
Move Move::add(const Move & m) const
{
    Move tmp;
    tmp.x = x + m.x;
    tmp.y = y + m.y;
    return tmp;
}
void Move::reset(double a, double b)
{
    x = a;
    y = b;
}

