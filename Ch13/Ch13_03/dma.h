//
// Created by tuser on 18-12-18.
//

#ifndef C_PRIMER_DMA_H
#define C_PRIMER_DMA_H

#include <iostream>

class abcDMA {
protected:
    char * label;
    int rating;

public:
    abcDMA(const char *l = "null", int r = 0);
    abcDMA(const abcDMA & ad);

    virtual ~abcDMA();
    abcDMA &operator=(const abcDMA & ad);
    virtual void View() = 0;
    friend std::ostream &operator<<(std::ostream &os, const abcDMA &ad);
};

// baseDMA继承于abcDMA，没有新增成员，不需要额外定义赋值运算符，析构函数，重载<<运算符。
class baseDMA : public abcDMA {
public:
    baseDMA(const char * l = "null", int r = 0);
    baseDMA(const abcDMA & ad);

    virtual void View();
};

// lacksDMA
// lacksDMA由于没有使用动态内存分配，所以不需要显示定义赋值运算符
// 也不需要显式的析构函数
class lacksDMA : public abcDMA {
private:
    enum {COL_LEN = 40};
    char color[COL_LEN];

public:
    lacksDMA(const char *c = "blank", const char *l = "null", int r = 0);
    lacksDMA(const char *c, const abcDMA & ad);
    lacksDMA(const lacksDMA & ls);

//    lacksDMA &operator=(const lacksDMA & ls);
    friend std::ostream &operator<<(std::ostream & os, const lacksDMA & ls);
    virtual void View();
};

// hasDMA
// 需要显式的析构函数和赋值运算符
class hasDMA : public abcDMA {
private:
    char * style;

public:
    hasDMA(const char * s = "none", const char * l = "null", int r = 0);
    hasDMA(const char * s, const abcDMA & ad);
    hasDMA(const hasDMA & hs);
    virtual ~hasDMA();

    hasDMA &operator=(const hasDMA & hs);
    friend std::ostream &operator<<(std::ostream & os, const hasDMA & hs);
    virtual void View();
};

#endif //C_PRIMER_DMA_H
