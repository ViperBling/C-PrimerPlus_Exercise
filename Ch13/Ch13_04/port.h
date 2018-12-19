//
// Created by tuser on 18-12-19.
//

#ifndef C_PRIMER_PORT_H
#define C_PRIMER_PORT_H

#include <iostream>
using namespace std;

class Port {
private:
    char * brand;
    char style[20];
    int bottles;

public:
    Port(const char *br = "none", const char *st = "none", int b = 0);
    Port(const Port & p);                           // 复制构造函数
    virtual ~Port() { delete [] brand; }
    Port &operator=(const Port & p);
    Port &operator+=(int b);                        // 瓶数加b
    Port &operator-=(int b);                        // 瓶数减b，如果瓶数足够的话

    int BottleCount() const { return bottles; }
    virtual void Show() const;
    friend ostream &operator<<(ostream & os, const Port & p);
};


class VintagePort : public Port {
private:
    char * nickname;
    int year;

public:
    VintagePort();
    VintagePort(const char * br, int b, const char * nn, int y);
    VintagePort(const VintagePort & vp);
    ~VintagePort() { delete [] nickname; }
    VintagePort &operator=(const VintagePort & vp);
    void Show() const;
    friend ostream &operator<<(ostream & os, const VintagePort & vp);
};

#endif //C_PRIMER_PORT_H
