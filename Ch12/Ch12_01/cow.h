//
// Created by tuser on 18-12-13.
//

#ifndef COW_H
#define COW_H

class Cow {
    char name[20];
    char * hobby;
    double weight;

public:
    Cow();              // 默认构造函数
    Cow(const char * nm, const char * ho, double wt);   // 构造函数
    Cow(const Cow & c);         // 复制构造函数
    ~Cow();                     // 析构函数
    Cow &operator=(const Cow & c);      // =运算符重载
    void ShowCow() const;               // 类方法，显示对象内容
};

#endif // COW_H
