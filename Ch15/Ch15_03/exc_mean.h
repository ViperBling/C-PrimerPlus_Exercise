//
// Created by tuser on 18-12-27.
//

#ifndef EXC_MEAN_H
#define EXC_MEAN_H

#include <iostream>
#include <stdexcept>
#include <sstream>

class basic : public std::logic_error {
private:
    double v1;
    double v2;
public:
    explicit basic(double a = 0, double b = 0, const std::string & s = "Invalid argument.")
            : v1(a), v2(b), logic_error(s) {}
    virtual void mesg() {
        std::cout << v1 << ", " << v2 << ": invalid argument.\n";
    }
};

class bad_hmean : public basic {
public:
    bad_hmean(double a = 0, double b = 0, const std::string & s = "Invalid argument: a = -b")
            : basic(a, b, s) {}
    void mesg() {
        std::cout << "hmean: " << std::endl;
        basic::mesg();
    }
};

class bad_gmean : public basic {
public:
    bad_gmean(double a = 0, double b = 0, const std::string & s = "Invalid argument: a < 0 or b < 0")
            : basic(a, b, s) {}
    void mesg() {
        std::cout << "gmean: " << std::endl;
        basic::mesg();
    }
};



#endif // EXC_MEAN_H
