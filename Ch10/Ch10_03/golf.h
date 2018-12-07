//
// Created by tuser on 18-12-7.
//

#ifndef GOLF_H
#define GOLF_H

#include <iostream>

class Golf {
private:
    std::string fullname;
    int handicap;

public:
    Golf();
    Golf(const std::string & fname, int handc = 0);
    void hcap(int n);
    void showgolf() const;
};

#endif // GOLF_H
