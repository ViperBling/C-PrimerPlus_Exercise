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

如果要派生出一个运动员在比赛中比分的类，则不必从头开始，只需要从`TableTennisPlayer`类中派生即可。

```C++
class RatedPlayer : public TableTennisPlayer {};
```

上面的声明头表示这是一个公有派生，`TableTennisPlayer`被称为公有基类。使用公有派生，基类的公有成员将成为派生类的公有成员，基类的私有部分也将成为派生类的一部分，但是只能通过基类的公有方法访问。

派生类中需要添加：

- 构造函数
- 根据需要添加额外的数据成员和成员函数

```C++
class RatedPlayer : public TableTennisPlayer {
private:
    unsigned int rating;
public:
    RatedPlayer(unsigned int r = 0, const string & fn = "none",
                const string & ln = "none", bool ht = false);
    RatedPlayer(unsigned int r, const TableTennisPlayer & tp);
    unsigned int Rating() const { return rating; }
    void ResetRating (unsigned int r) { rating = r; }
};
```

### 13.1.2 构造函数：访问权限的考虑

在创建派生类对象的时候，首先会创建基类对象，然后，基类对象通过基类本身构造函数**成员初始化列表**的方法传入派生类。如果不显式的指明基类构造函数，那么将使用基类的默认构造函数，而这一点不总是正确的。总的来说：

- 首先创建基类对象
- 派生类构造函数应通过成员初始化列表将基类信息传递给基类构造函数
- 派生类构造函数应初始化派生类新增的成员

### 13.1.3 使用派生类

### 13.1.4 派生类和基类之间的特殊关系

关系：

- 派生类可以使用基类的公有方法

  ```C++
  RatedPlayer rplayer1(1140, "Mallory", "Duck", true);
  rplayer1.Name(); 			// 使用基类的Name方法
  ```

- 基类的指针可以在不进行显式类型转换的情况下指向派生类对象

- 基类的引用可以在不进行显式类型转换的情况下引用派生类对象

  ```C++
  RatedPlayer rplayer1(1140, "Mallory", "Duck", true);
  TableTennisPlayer & rt = rplayer1;			// 引用派生类对象
  TableTennisPlayer * pt = rplayer1;			// 指向派生类对象
  ```

  但是要注意，这种指针和引用只能使用基类的方法，不能使用派生类的方法。而且不能反过来：

  ```C++
  TableTennisPlayer player("Betsy", "Bloop", true);
  RatedPlayer & rt = player;					// 不可以！
  RatedPlayer * pt = player;					// 不可以！
  ```

允许基类的引用隐式的引用派生类对象，则可以使用基类的引用为派生类调用基类的方法，这样是合理的。因为派生类继承于基类，可以使用基类的方法。但是反过来，允许派生类引用引用基类对象，这样是没有意义的，因为基类无法使用派生类的方法。

上面的这种特性将引发一些有趣的现象，详情看**p489**

## 13.2 继承：is - a关系

C++三种继承方式：公有继承、保护继承、私有继承。上述的就是公有继承的一个例子。它建立了一种`is-a`关系（is-a-kind-of）。因为`RatedPlayer`类可以看做是添加了`rating`成员的`TableTennisPlayer`类，它可以使用基类的所有公有方法。

公有继承不能建立`has-a`关系：例如午餐可以有水果，但是午餐不一定水果。但上面的`RatedPlayer`对象一定是`TableTennisPlayer`对象，这两种显然是不同的关系。前者是一种`has-a`的关系。但是可以将水果对象作为午餐类的数据成员实现这种关系。

公有继承也不能建立：`is-like-a`关系、`is-implemented-as-a`关系、`uses-a`关系。

## 13.3 多态公有继承

上述`RatedPlayer`类使用基类的方法，并未做任何修改。但是有的时候会希望同一个方法在基类和派生类中表现出不同的行为，这就是多态。有两种方法可以实现：

- 在派生类中重新定义基类的方法
- 使用虚方法

课本中的例子，开发`BrassAccount`类和`BrassPlus`类：

`BrassAccount`数据成员：客户姓名、账号、当前结余

`BrassAccount`成员方法：创建账户、存款、取款、显示账户信息。

`BrassPlus`数据成员：`BrassAccount`的所有信息，透支上限、透支贷款利率、当前透支总额

`BrassPlus`成员方法：使用`BrassAccount`的成员方法，但是需要有新操作。

- 考虑透支保护
- 现实操作必须显示`BrassPlus`的信息。

### 13.3.1 开发`Brass`和`BrassPlus`类

```C++
//
// Created by tuser on 18-12-17.
//

#ifndef C_PRIMER_BRASS_H
#define C_PRIMER_BRASS_H
#include <string>

class Brass {
private:
    std::string fullName;				// 客户姓名
    long acctNum;						// 客户账号
    double balance;						// 当前结余
public:
    Brass(const std::string & s = "Nullbody", long an = -1,
          double bal = 0.0);
    void Deposit(double amt);			
    virtual void Withdraw(double amt);	// 取款
    double Balance() const;
    virtual void ViewAcct() const;		// 显示账户信息
    virtual ~Brass() {}
};

class BrassPlus : public Brass {
private:
    double maxLoan;						// 透支上限
    double rate;						// 透支利率
    double owesBank;					// 欠款
public:
    BrassPlus(const std::string & s = "Nullbody", long an = -1,
              double bal = 0.0, double m1 = 500, double r = 0.11125);
    BrassPlus(const Brass & ba, double m1 = 500, double r = 0.11125);
    virtual void ViewAcct() const;
    virtual void Withdraw(double amt);
    void ResetMax(double m) { maxLoan = m; }
    void ResetRate(double r) { rate = r; }
    void ResetOwes() { owesBank = 0; }
};

#endif // C_PRIMER_BRASS_H
```

- 上述类声明中定义了两个`ViewAcct`方法和`Withdraw`方法，这两个方法在不同类中的行为不同，具有独立的方法定义：

  ```C++
  Brass dom("Dominic Banker", 11224, 4183.45);
  BrassPlus dot("Dorothy Banker", 12118, 2592.00);
  dom.ViewAcct();				// 使用Brass::ViewAcct()
  dot.ViewAcct();				// 使用BrassPlus::ViewAcct()
  ```

- 上述代码中还使用了新的关键字`virtual`。`virtual`关键字可以指明，如果方法是通过引用或指针调用时，应该使用哪种方法。具体来说，如果没有`virtual`关键字，那么使用引用或者指针调用方法时，使用的是引用或者指针本身类型的方法：

  ```C++
  // 没有virtual关键字
  Brass dom("Dominic Banker", 11224, 4183.45);
  BrassPlus dot("Dorothy Banker", 12118, 2592.00);
  Brass & b1_ref = dom;
  Brass * b2_ref = dot;
  b1_ref.ViewAcct();			// 使用Brass::ViewAcct()
  b2_ref.ViewAcct();			// 使用Brass::ViewAcct()
  ```

  如果使用了`virtual`关键字，那么使用的方法是引用或指针指向的对象类型的方法：

  ```C++
  // 有virtual关键字
  Brass dom("Dominic Banker", 11224, 4183.45);
  BrassPlus dot("Dorothy Banker", 12118, 2592.00);
  Brass & b1_ref = dom;
  Brass * b2_ref = dot;
  b1_ref.ViewAcct();			// 使用Brass::ViewAcct()
  b2_ref.ViewAcct();			// 使用BrassPlus::ViewAcct()
  ```

## 13.4 静态联编和动态联编

将源代码中的函数调用解释为执行特定的函数代码块被称为函数名联编。C语言中，由于每个函数名只对应一个函数，所以很简单。在C++中，由于函数重载，比较复杂。编译器在编译的过程中进行联编，被称为**静态联编**。但是还有虚函数的存在，这种情况下不能在编译过程中确定要使用的函数版本，所以就有了**动态联编**。

### 13.4.1 指针和引用类型的兼容性

将派生类的引用或指针转换为基类的引用或指针被称为向上强制转换，这种转换不需要显式指出，而且是可传递的。

将基类的引用或指针转换为派生类的引用或指针被称为向下强制转换，如果不允许显式的强制转换，通常是没有意义的。

对于基类引用或指针作为函数参数的函数调用，将进行向上转换。这种隐式的向上强制转换需要动态联编，**虚成员函数**可以满足这种要求。

### 13.4.2 虚成员函数和动态联编

#### 1. 为什么使用两种类型的联编

动态联编效率较静态联编低。有些方法不需要动态联编，不需要重新定义，比如`Brass::Balance()`。

#### 2. 虚函数的工作原理

编译器会给每个对象添加一个隐藏的成员，其中保存了一个指向函数地址数组的指针，这个数组被成为虚函数表（vtbl）。vtbl中保存了为类声明的虚函数的地址。例如，声明一个`Brass`类对象`dom`，则在程序执行中，会到基类的vtbl中寻找虚函数地址并执行，而派生类`BrassPlus`有一个单独的vtbl，如果没有对基类的方法进行重新定义，那么其vtbl中保存的函数地址和基类是相同的，如果重新定义了方法，那么会有一个新的函数地址被添加到派生类的vtbl中。同样，在程序执行过程中，也会查表，然后执行对应的虚函数。

### 13.4.3 有关虚函数的注意事项

- 基类中使用了`virtual`关键字的方法在基类和所有派生类中为虚的。
- 使用指向对象的引用或指针调用虚方法，将使用动态联编
- 如果定义的类为基类，那么需要在派生类中重新定义的方法应该被声明为虚的。

#### 1. 构造函数

构造函数不能是虚函数

#### 2. 析构函数

析构函数应当是虚函数。通常应该给基类提供一个虚析构函数，即使它并不需要析构函数。

#### 3. 友元

友元不能是虚函数，因为它不是类成员。但是它可以调用虚方法。

#### 4. 没有重新定义

没有重新定义的情况下，不需要使用虚函数。

#### 5. 重新定义将隐藏方法

如果在派生类中重新定义了基类的方法，而且特征标不同，那么将会隐藏基类的方法，这会导致基类的方法不能被正确调用。所以要注意：

- 如果重定义继承方法，应确保与原来的原型完全相同。但是返回类型可以定义为派生类的引用或指针。

- 如果基类声明被重载了，则应在派生类中重新定义所有的基类版本。

  ```C++
    class Dwelling {
    public:
        virtual void showperks(int a) const;		// 重载方法
        virtual void showperks() const;
    };
    class Hovel : public Dwelling {
    public:
        virtual void showperks(int a) const;		// 在派生类中应该重载所有基类方法
        virtual void showperks() const;
    };
  ```

## 13.5 访问控制：protected

关键字`protected`和`private`类似，在类外只有公有成员才能访问`protected`中的成员。但是派生类可以访问基类中`protected`部分的类成员，不能访问`private`部分的类成员。

## 13.6 抽象基类（Abstract Bases Class，ABC）

假设有一个椭圆类`Ellipse`，有一个圆的类`Circle`。它们具有一些共性，所有的圆都是椭圆。但是也有一些不同，例如描述一个`Ellipse`对象，可能需要长轴、短轴等，但是圆只需要一个半径即可。所以如果简单的将圆从椭圆中派生出来，比较笨拙。一种解决方法就是从`Ellipse`和`Circle`中抽象出其共性，放到一个ABC中，然后从ABC中派生出`Ellipse`和`Circle`。

比如，`Ellipse`和`Circle`的共同点有中心坐标、`Move()`方法和`Area()`方法，但是`Area()`方法对于两个派生类来说是不一样的，所以无法在ABC中定义`Area()`方法。这就需要把`Area()`方法定义为**纯虚函数**：

```C++
class BaseEllipse {		// 抽象基类
private:
    double x;
    double y;
public:
    BaseEllipse(double x0 = 0, double y0 = 0) : x(0), y(0) {}
    virtual ~BaseEllipse() {}
    void Move(int nx, ny) {x = nx; y = ny;}
    virtual double Area() const = 0;			// 纯虚函数
}		
```

包含纯虚函数的类只能是基类，而且不能创建对象。但是可以通过派生具体类的方式来创建对象，例如派生出`Ellipse`和`Circle`类。ABC描述的是至少使用一个纯虚函数的接口，从ABC派生出的类将根据派生类的具体特征使用常规虚函数来实现这种接口。

### 13.6.1 应用ABC概念

将ABC用于Brass和BrassPlus类。

### 13.6.2 ABC理念

在设计ABC之前，首先应该开发一个模型，指出编程问题所需要的类以及它们之间的关系。然后将那些不会被用作基类的类设计为具体的类。可以将ABC看做一种接口，因为它要求派生类必须覆盖其纯虚函数，也就是迫使派生类遵循ABC设置的接口规则。

## 13.7 继承和动态内存分配

### 13.7.1 第一种情况：派生类不使用new

如果派生类没有使用new，那么在派生类中不需要显式的定义析构函数、复制构造函数、赋值运算符。因为，在基类中已经定义了相关函数，在派生类中调用时，直接使用基类的相关方法。

### 13.7.2 第二种情况：派生类使用new

当基类和派生类都采用动态内存分配时，派生类的析构函数、复制构造函数、赋值运算符都必须使用相应的基类方法来处理基类元素。有三种情况：

- 析构函数，自动完成
- 构造函数，通过初始化成员列表中调用基类的复制构造函数完成
- 赋值运算符，显式的使用域解析运算符调用基类的赋值运算符。

### 13.7.3 使用动态内存分配和友元的继承示例

派生类使用友元：

```C++
friend std::ostream &operator<<(std::ostream & os, const lacksDMA & ls);

std::ostream &operator<<(std::ostream & os, const lacksDMA & ls) {
    os << (const baseDMA &) ls;
    os << "Style: " << hs.style << endl;
    return os;
}
```

可以看到，因为在基类中已经重载过了`<<`运算符，所以，在派生类中直接使用重载的运算符显示基类的部分，然后剩余部分继续重载即可。

## 13.8 类设计回顾

### 13.8.1 编译器生成的成员函数

#### 1. 默认构造函数

默认构造函数要么没有参数，要么所有的参数都有默认值。并且如果派生类的构造函数初始化成员列表中没有显式的调用基类构造函数，那么编译器则使用基类的默认构造函数。

#### 2. 复制构造函数

#### 3. 赋值运算符

### 13.8.2 其他的类方法

#### 1. 构造函数

构造函数不被继承

#### 2. 析构函数

注意要使用显式的析构函数释放`new`分配的内存。

#### 3. 转换

如果一个构造函数只使用了一个参数，那么将引发从参数类型到类类型的转换。

```C++
Star(const char *);

Star north;
north = "polaris";
```

上述代码第4行将调用第一行的构造函数，使用隐式的类型转换。如果加入`explicit`关键字将禁止隐式转换，但是仍然可以显式转换：

```C++
class Star {
public:
    explicit Star(const char *);
}

Star north;
north = "polaris";			// 不能这么做
north = Star("polaris");	// 加入explicit后的做法
```

#### 4. 按值传递对象与传递引用

#### 5. 返回对象与返回引用

如果被调函数在执行过程中创建了临时对象，那么应该返回对象而不是引用。

#### 6. 使用`const`

### 13.8.3 公有继承的考虑因素

#### 1. is-a关系

在继承的时候要考虑is-a关系，最好是使用包含纯虚函数的抽象数据类派生出其他类。

#### 2. 什么不能被继承

构造函数、析构函数、赋值运算符不能被继承。

#### 3. 赋值运算符

如果不显式定义赋值运算符，那么编译器会自动提供一个赋值运算符给类，但是这个默认的赋值运算符是采用成员赋值的，对于字符串等指针类型如果使用了`new`运算符，为了避免被多次释放，需要深复制，就需要显式定义赋值运算符。

如果派生类和基类都定义了赋值运算符，那么可以将派生类赋值给基类，但是不能反过来。因为派生类不能自动引用基类对象，除非定义了转换函数。

#### 4. 私有成员和保护成员

对于派生类来说，保护成员类似于公有成员，但是对外部而言，保护成员和私有成员类似。派生类可以直接访问基类的保护成员，但是只能通过类方法访问基类的私有成员。

#### 5. 虚方法

设计基类时，如果希望在派生类中重新定义方法，则应在基类将其定义为虚的，这样可以启用动态联编。

#### 6. 析构函数

析构函数应该是虚的。

#### 7. 友元函数

友元函数不能继承，但是如果希望使用基类的友元，可以通过强制类型转换，将派生类的引用或指针转换成基类的引用或指针，然后使用转换后的引用或指针来调用基类的友元函数。

#### 8. 有关使用基类方法的说明

