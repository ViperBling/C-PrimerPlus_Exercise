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

