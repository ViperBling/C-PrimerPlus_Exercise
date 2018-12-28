//
// Created by tuser on 18-12-27.
//

#ifndef EXC_MEAN_H
#define EXC_MEAN_H

#include <iostream>
#include <stdexcept>

class bad_hmean : public std::logic_error{
public:
    explicit bad_hmean(const std::string & s = "Invalid argument: a = -b")
            : logic_error(s) {}
};

class bad_gmean : public std::logic_error {
public:
    explicit bad_gmean(const std::string & s = "Invalid argument: a < 0 or b < 0")
            : logic_error(s) {}
};



#endif // EXC_MEAN_H
