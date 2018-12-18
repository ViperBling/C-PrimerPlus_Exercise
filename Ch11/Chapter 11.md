[TOC]

# Chapter 11. 使用类

## 11.1 运算符重载

C++允许将运算符重载扩展到用户自定义的类型，例如允许两个类相加。这种加法隐藏了内部机理，并强调了实质。

```C++
operator*();
operator+();
```

## 11.2 运算符重载示例

### 11.2.1 添加加法运算符

原来的类声明：

```C++
class Time{
  private:
    int hours;
    int minutes;
    
  public:
    Time();
    Time(int h, int m = 0);
    void AddMin(int m);
    void AddHr(int h);
    void Reset(int h = 0, int m = 0);
    Time Sum(const Time & t) const;		// 运算符重载之前的方法原型
    void Show() const;
};
```

重载运算符只要将`Sum`函数重新声明为`operator+()`即可：

```C++
Time operator+(const Time & t) const;
```

而方法定义不需要修改。这样修改完成后，可以使用运算符重载来调用方法：

```C++
total = coding.operator+(fixing);		// 按照未重载运算符之前的方法调用
total = coding + fixing;				// 运算符重载，使用类加法
```

同时，这种重载方式也支持连加法。因为+运算符的结合顺序为从左到右，所以：

```C++
Time t, t1, t2, t3;
t = t1 + t2 + t3;
```

等同于：

```C++
t = t1.operator+(t2 + t3);		// 等同于下面语句
t = t1.operator+(t2.operator+(t3));
```

所以是合法的。

### 11.2.2 重载限制

1. 重载后的运算符必须至少有一个操作数是用户自定义类型。

2. 使用运算符不能违反原来运算符的句法规则：`% x`非法

3. 不能创建新的运算符

4. 不能重载下面运算符：

   ```C++
   sizeof;
   .;
   .*;
   ::;
   ?:;
   typeid:	一个RTTI运算符
   const_cast:	强制类型转换运算符
   dynamic_cast: 同上
   reinterpret_cast: 同上
   static_cast: 同上
   ```

5. 大多数运算符可以通过成员或非成员函数重载，但是下面的运算符只能通过成员函数重载：

   ```C++
   =： 赋值运算符
   (): 函数调用运算符
   []: 下标运算符
   ->: 通过指针访问类成员运算符
   ```

### 11.2.3 其他重载运算符

可以按照重载+运算符的方式重载其他运算符。

## 11.3 友元

类的数据只有类的成员函数可以访问，这种限制有时太过严格，C++提供了另外一种访问方式，友元：

- 友元函数；
- 友元类
- 友元成员函数

### 11.3.1 创建友元

```C++
// 友元声明
friend Time operator*(double m, const Time & t);	// 原型放在类声明中
```

 `operator*()`是在类中声明的，但不是成员函数，所以不能使用成员运算符，但是它和成员函数的访问权限相同。

   ```C++
// 友元定义，没有friend关键字
Time operator*(double m, const Time & t);
   ```

### 11.3.2 常用友元：重载<<运算符

如果想让：`cout << trip`起作用怎么操作呢？其中`trip`是前面定义的`Time`类对象。

#### 1. <<的第一种重载版本

如果使用类的成员函数来重载<<，那么只能像下面这样使用：

   ```C++
   trip << cout;	// 有点奇怪
   ```

通过上面说的友元，就可以完成重载：

   ```C++
   void operator<<(ostream & os, const Time & t)
   {
       os << t.hours << " hours, " << t.minutes << " minutes";
   }
   ```

这样就可以按照正常习惯使用：`cout << trip`

#### 2. <<的第二种重载版本

第一个版本中可以这样使用`<<`运算符：`cout << trip`，但不允许将重载的`<<`和`cout`一起使用：

   ```C++
   cout << "Trip time: " << trip << " (Tuesday)\n";	// 不能这么做
   ```

`cout`是一个`ostream`对象，对于语句`cout << x << y`，由于从左往右结合，所以`cout << x`表达式也是一个`ostream`对象，所以可以连续输出。那么，如果我们也想这样，只要将第一个版本的友元函数修改成返回`ostream`引用就可以了：

   ```C++
   ostream & operator<<(ostream & os, const Time & t)
   {
       os << t.hours << " hours, " << t.minutes << " minutes";
       return os;
   }
   ```

## 11.4 重载运算符：作为成员函数还是非成员函数

两种格式不能同时选择，否则会出现二义性错误。

## 11.5 再谈重载：一个矢量类

构建一个矢量类：

   ```C++
   #ifndef C_PRIMER_VECT_H
   #define C_PRIMER_VECT_H
   
   #include <iostream>
   
   namespace VECTOR
   {
       class Vector{
       public:
           enum Mode {RECT, POL};	// RECT代表直角坐标，POL代表极坐标
       private:
           double x;			// x轴
           double y;			// y轴
           double mag;			// 极坐标长度
           double ang;			// 极坐标角度
           Mode mode;			// RECT or POL
           void set_mag();		// 私有方法，用来设置值
           void set_ang();
           void set_x();
           void set_y();
   
       public:
           // 默认构造函数
           Vector();
           // 构造函数
           Vector(double n1, double n2, Mode form = RECT);
           void reset(double n1, double n2, Mode form = RECT);
           ~Vector();								// 析构函数
           double xval() const { return x; }		// 内联函数，返回对应值
           double yval() const { return y; }
           double magval() const { return mag; }
           double angval() const { return ang; }
           void polar_mode();						// 将模式转换为极坐标
           void rect_mode();						// 将模式转换为直角坐标
           Vector operator+(const Vector & b) const;	// 加法重载
           Vector operator-(const Vector & b) const;	// 减法重载
           Vector operator-() const;					// 反转
           Vector operator*(double n) const;			// 数乘
   		
           // 友元重载
           friend Vector operator*(double n, const Vector & a);
           // <<重载
           friend std::ostream &operator<<(std::ostream & os, const Vector & v);
       };
   }
   
   #endif //C_PRIMER_VECT_H
   ```

### 11.5.1 使用状态成员

上述定义中，枚举变量`Mode`中的`RECT`和`POL`被称为状态成员。

### 11.5.2 为Vector类重载算术运算符

在上面重载加法的时候，可以使用如下的重载方法：

   ```C++
   Vector Vector::operator+(const Vector & b) const {
       Vector sum;
       sum.x = x + b.x;
       sum.y = y + b.y;
       return sum;
   }
   ```

但是这种方法不能重载极坐标的加法。为此，可以直接调用构造函数实现：

   ```C++
   Vector Vector::operator+(const Vector & b) const {
       return Vector(x + b.x, y + b.y);
   }
   ```

#### 1. 乘法

可以看到，上面类接口定义中，成员函数重载了数乘的左乘，友元函数重载了数乘的右乘。

#### 2. 对已重载的运算符进行重载

从类接口定义中看到，`-`运算符被重载了两次，第一次是矢量减法，第二次是矢量反转

### 11.5.4 使用Vector来模拟随机漫步

## 11.6 类的自动转换和强制类型转换

C++内置类型之间如果类型兼容，可以进行类型自动转换。现在用户自定义的类型也可以实现转换。

   ```C++
   Stonewt myCat;
   myCat = 19.6;
   ```

这样，就可以`double`类型转换成`myCat`类型，前提是自定义类型中提供了相应的转换函数，一般通过构造函数来实现。但是这种自动转换不总是正确的，有时候可能会导致意外的结果。所以C++中提供了关键字`explicit`来关闭这种隐式转换，但是仍然可以使用显式转换：

   ```C++
   explicit Stonewt(double lbs);		// 关闭隐式转换
   
   Stonewt myCat;
   myCat = 19.6;						// 不能再使用
   myCat = Stonewt(19.6);				// 以下两种都是合法的显式转换
   myCat = (Stonewt) 19.6;				// 旧的形式
   ```

### 11.6.1 转换函数

前面说过，可以将数字转换成`Stonewt`对象，但是反过来呢？

   ```C++
   Stonewt wolfe(285.7);
   double host = wolfe; 		// 可以吗？
   ```

可以这样做，但是需要使用转换函数。

   ```C++
   #ifndef STONEWT1_H_
   #define STONEWT1_H_
   class Stonewt {
   private:
       enum {Lbs_per_stn = 14};
       int stone;
       double pds_left;
       double pounds;
       
   public:
       Stonewt(double lbs);				// 英镑形式的构造函数
       Stonewt(int stn, double lbs);		// 英石形式的构造函数
       Stonewt();							// 默认构造函数
       ~Stonewt();
       void show_lbs() const;				// 以英镑形式显示重量
       void show_stn() const;				// 以英石方式显示重量
      	// 转换函数
       operator int() const;
       operator double() const;
   }；
   #endif
   ```

转换函数的函数定义如下：

   ```C++
   Stonewt::operator int () const {
       return int(pounds + 0.5);
   }
   
   Stonewt::operator double () const {
       return pounds;
   }
   ```

使用转换函数时需要注意：

   - 转换函数必须是类方法；
   - 转换函数不能指定返回类型；
   - 转换函数不能有参数。

### 11.6.2 转换函数和友元函数
