[TOC]

# Chapter 15. 友元、异常和其他

- 友元类
- 友元类方法
- 嵌套类
- 引发异常、try块和catch块
- 异常类
- 运行阶段类型识别（RTTI）
- dynamic_cast和typeid
- static_cast、const_cast和reiterpret_cast

## 15.1 友元

友元类的所有方法都可以访问原始类的私有成员和保护成员，另外，也可以做严格的限制。

### 15.1.1 友元类

例如一个遥控器类和一个TV类，它们两个既不是is-a关系，也不是has-a关系。由于遥控器可以改变TV的状态，那么可以将Remote类作为TV类的一个友元。

```C++
#ifndef C_PRIMER_TV_H
#define C_PRIMER_TV_H

class Tv {
private:
    int state;
    int volume;
    int maxchannel;
    int channel;
    int mode;
    int input;
    
public:
    friend class Remote;				// 友元类声明
    enum {Off, On};
    enum {MinVal, MaxVal = 20};
    enum {Antenna, Cable};
    enum {TV, DVD};
    
    Tv(int s = Off, int mc = 125) 
            : state(s), volume(5), maxchannel(mc), channel(2), mode(Cable), input(TV) {}
    void onoff() { state = (state == On) ? Off : On; }            
    bool ison() const { return state == On; }
    bool volup();
    bool voldown();
    void chanup();
    void chandown();
    void set_mode() { mode = (mode == Antenna) ? Cable : Antenna; }
    void set_input() { input = (input == TV) ? DVD : TV; }
    void settings() const;
};

class Remote {
private:
    int mode;
public:
    Remote(int m = Tv::TV) : mode(m) {}
    bool volup(Tv & t) { return t.volup(); }
    bool voldown(Tv & t) { return t.voldown(); }
    void onoff(Tv & t) { t.onoff(); }
    void chanup(Tv & t) { t.chanup(); }
    void chandown(Tv & t) { t.chandown(); }
    void set_chan(Tv & t, int c) { t.channel = c; }		// 访问友元类的私有成员
    void set_mode(Tv & t) { t.set_mode(); }
    void set_input(Tv & t) { t.set_input(); }
};

#endif //C_PRIMER_TV_H
```

### 15.1.2 友元成员函数

上一个例子中，只有`Remote::set_chan()`方法直接访问了`Tv`成员。其实可以限定只让友元访问指定的成员：

```C++
class Tv {
    friend void Remote::set_chan(Tv & t, int c);
}
```

这样，`Remote`的定义需要在`Tv`之前，又由于`Remote`中提到了`TV`类，所以`Remote`要在`Tv`之前，这就产生了循环依赖，为了解决这个问题，需要使用前向声明。总的来说，定义顺序如下：

```C++
class Tv;			// 前向声明
class Remote {...};
class Tv {...};
```

这样可以解决一部分问题。`Remote`类中还有一部分内联代码，例如：

```C++
void onoff(Tv & t) { t.onoff(); }
```

这就要求`Tv`的定义要出现在这些内联代码之前，与前面又矛盾了。解决方法是，在`Remote`中只声明，不定义，将定义放在`Tv`类的后面，以内联函数的方式给出：

```C++
class Tv;
class Remote {
    ...;
    void onoff(Tv & t);
};
class Tv {...};
inline void Remote::onoff(Tv & t) { t.onoff(); }
```

### 15.1.3 其他友元关系

除了`Remote`可以是`Tv`的友元外，`Tv`也可以是`Remote`的友元。

### 15.1.4 共同的友元

如果希望函数同时访问两个类的私有数据，就需要使用共同的友元。

## 15.2 嵌套类

可以将一个类的声明放在另一个类中，这种被称为嵌套类。注意包含类和嵌套类的区别，包含类是将类作为数据成员，嵌套类是在另一个类中定义一个类，而且仅在嵌套类声明的类中有效。

```C++
class Queue {
    class Node {
    public:
        Item item;
        Node * next;
        Node(const Item &i) : item(i), next(0) {}
    };
    ...
}
```

### 15.2.1 嵌套类和访问权限

#### 1. 作用域

如果嵌套类是在另一个类的**私有部分**被声明的，那么它只对后者可见。也就是说，类的其他部分甚至不知道嵌套类的存在。对于类的外部，例如派生类，也是不可以见的。

如果嵌套类是在另一个类的**保护部分**被声明的，那么，它对后者的所有部分是可见的，但对于外部世界不可见。然而，派生类可以知道嵌套类的存在，并且可以使用嵌套类。

如果嵌套类是在另一个类的**公有部分**被声明的，那么它对所有部分是可见的。但是在外部使用嵌套类的时候必须加上作用域解析运算符。

| 声明位置 | 包含它的类是否可以使用它 | 从包含它的类派生的类是否可以使用它 | 在外部是否可以使用 |
| :------: | :----------------------: | :--------------------------------: | :----------------: |
| 私有部分 |            是            |                 否                 |         否         |
| 保护部分 |            是            |                 是                 |         否         |
| 公有部分 |            是            |                 是                 |  是，通过类限定符  |

#### 2. 访问控制

类可见后，起决定性作用的将是访问控制（公有、保护、私有、友元）。

### 15.2.2 模板中的嵌套

在模板中包含嵌套类时不会带来其他多余的问题。套就是了。

## 15.3 异常

计算调和平均值：`2.0 * x * y / (x + y)`。

### 15.3.1 调用`abort()`

对于上述调和平均值，如果`x = -y`，会出现除0的情况。为了处理这种问题，可以使用`abort()`函数。

```C++
#include <iostream>
#include <cstdlib>

double hmean(double a, double b);

int main()
{
    double x, y, z;

    std::cout << "Enter two numbers: ";
    while (std::cin >> x >> y) {
        z = hmean(x, y);
        std::cout << "Harmonic mean of " << x << " and " << y
                  << " is " << z << std::endl;
        std::cout << "Enter next set of numbers <q to quit>: ";
    }
    std::cout << "Bye!\n";

    return 0;
}

double hmean(double a, double b) {
    if (a == -b) {
        std::cout << "Untenable arguments to hmean()\n";
        std::abort();
    }
    return 2.0 * a * b / (a + b);
}
```

### 15.3.2 返回错误码

可以让函数返回成功或者失败来表示运行情况，运算结果使用指针参数，如果为不合法值，将返回一个错误的标志。

### 15.3.3 异常机制

C++异常是对程序运行过程中发生的异常情况的一种响应，它提供了将控制权从程序的一部分转移到另一部分的一种途径。

- 引发异常
- 使用处理程序捕获异常
- 使用try块

```C++
#include <iostream>
#include <cfloat>

double hmean(double a, double b);

int main()
{
    double x, y, z;

    std::cout << "Enter two numbers: ";
    while (std::cin >> x >> y) {
        try {					
            z = hmean(x, y);
        }
        catch (const char * s) {
            std::cout << s << std::endl;
            std::cout << "Enter a new pair of numbers: ";
            continue;
        }
            std::cout << "Harmonic mean of " << x << " and " << y
                      << " is " << z << std::endl;
        std::cout << "Enter next set of numbers <q to quit>: ";
    }
    std::cout << "Bye!\n";

    return 0;
}

double hmean(double a, double b) {
    if (a == -b)
        throw "bad hmean() arguments: a = -b not allowed";
    else
        return 2.0 * a * b / (a + b);
}
```

try是要测试是否出现异常的代码块，`throw`关键字代表引发异常，通常后面跟的是异常特征值（字符串或对象）。`catch`表示捕获异常，参数列表是表示异常类型。例如上述例子中，`throw`检测到`a=-b`时，抛出了异常，异常值为字符串类型，则`catch`中也捕获对应的类型。`catch`捕获异常后，包含的代码块对异常进行处理。这里只是介绍了大概的原理，详情见**p620**。

### 15.3.4 将对象用作异常类型

通常可以让引发异常的函数传递一个对象，可以更加细致地区分异常的类型，并且对象可以携带信息，方便查找原因。

```C++
class bad_hmean {
private:
    double v1;
    double v2;
public:
    bad_hmean(int a = 0, int b = 0) : v1(a), v2(b) {}
    void mesg();
};
inline void bad_hmean::mesg() {
    std::cout << "hmean(" << v1 << ", " << v2 << "): "
        	  << "invalid arguments: a = -b\n";
}
...
if (a == -b)
    throw bad_hmean(a, b);			// 引发异常
```

上述代码引发异常后，返回了一个对象，保存了对应的异常信息，也就是a, b的值。

### 15.3.5 异常规范和C++11

一种已经被摒弃的理念：

```C++
double harm(double a) throw(bad_thing);
```

作用之一是告诉用户可能需要`try`块；另一个作用是告诉编译器检查是否违反了异常规范。不建议使用，忽略这部分内容吧，当它不存在。

### 15.3.6 栈解退

