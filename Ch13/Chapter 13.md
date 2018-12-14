[TOC]

# Chapter 13. 类继承

- is-a关系继承
- 以公有方式派生类
- 保护访问
- 构造函数成员初始化列表
- 向上和向下强制转换
- 虚成员函数
- 早期（静态）联编与晚期（动态）联编
- 抽象基类
- 纯虚函数
- 何时及如何使用公有继承

## 13.1 一个简单的基类

原始类为基类，继承出来的成为派生类。

初始化一个乒乓球运动员的基类：

```C++
#ifndef C_PRIMER_TABTENN0_H
#define C_PRIMER_TABTENN0_H

#include <string>
using std::string;

class TableTennisPlayer {
private:
    string firstname;
    string lastname;
    bool hasTable;

public:
    TableTennisPlayer(const string & fn = "none",
                      const string & ln = "none", bool ht = false);
    void Name() const;
    bool HasTable() const { return hasTable; };
    void ResetTable(bool v) { hasTable = v; };
};

#endif //C_PRIMER_TABTENN0_H
```

### 13.1.1 派生一个类

如果要派生出一个运动员在比赛中比分的类，