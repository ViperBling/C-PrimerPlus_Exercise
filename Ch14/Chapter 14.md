[TOC]

# Chapter 14. C++中的代码重用

- has-a关系
- 包含对象成员的类
- 模板类valarray
- 私有和保护继承
- 多重继承
- 虚基类
- 创建类模板
- 使用类模板
- 模板的具体化

## 14.1 包含对象成员的类

### 14.1.1 valarray类简介

`valarray`是一个模板类，提供了对数值数组各种计算的支持：

```C++
valarray<double> v1;				// 声明一个含有0个元素的空数组
valarray<int> v3(10, 8); 			// 声明一个含有8个int的数组，每个元素都被初始化为10
```

### 14.1.2 Student类的设计

使用一个`string`表示姓名，一个`valarray<double>`表示考试分数。这里`Student`类和前面这两个类就是一种has-a关系。通常用于建立has-a关系的技术叫组合，即创建一个包含其他类的类。组合和公有继承不同，公有继承既继承了接口，也继承了实现，也就是说，继承了基类的方法；而组合只继承了类的成员，但不继承接口。例如，上述`Student`类中的姓名，如果继承了`string`类中的`operator+=`方法，这是没有意义的。

```C++
class Student {
private:
    string name;
    valarray<double> scores;
};
```

### 14.1.3 Student类示例

```C++
#ifndef C_PRIMER_STUDENT_H
#define C_PRIMER_STUDENT_H

#include <iostream>
#include <string>
#include <valarray>

class Student {
private:
    typedef std::valarray<double> ArrayDb;
    std::string name;
    ArrayDb scores;
    // 输出scores数组的私有方法
    std::ostream &arr_out(std::ostream & os) const;

public:
    Student() : name("Null Student"), scores() {}
    explicit Student(const std::string &s) : name(s), scores() {}
    explicit Student(int n) : name("Nully"), scores(n) {}
    Student(const std::string & s, int n) : name(s), scores(n) {}
    Student(const std::string & s, const ArrayDb & a) : name(s), scores(a) {}
    Student(const char * str, const double *pd, int n) : name(str), scores(pd, n) {}
    ~Student() {}
    double Average() const;
    const std::string & Name() const;
    double &operator[](int i);
    double operator[](int i) const;
// friends
	// input    
    friend std::istream &operator>>(std::istream & is, Student & stu);
    friend std::istream &getline(std::istream & is, Student & stu);
    // output
    friend std::ostream &operator<<(std::ostream & os, const Student & stu);
};

#endif //C_PRIMER_STUDENT_H
```

关于`explicit`的使用：

上面代码的第18,19行使用了`explicit`关键字来关闭隐式转换。对于第19行的构造函数而言，如果不使用`explicit`关键字，那么下面的代码将是允许的：

```C++
Student doh("Homer", 10);			// 存储"Homer"，并创建一个10元素数组
doh = 5;							// 重置名称为"Nully"，并创建一个5元素数组
```

所以，如果省略了`explicit`，那么将使用`Student(5)`将5转换为一个临时`Student`对象，并使用`Nully`来设置`name`的值。

#### 1. 初始化被包含的对象

上述代码中，使用了成员初始化列表来初始化成员：

```C++
Student(const char *str, const double *pd, int n) : name(str), scores(pd, n) {}
```

这里初始化列表里使用的是成员名而不是类名（在前面有过例子），每一项都会调用与之匹配的构造函数。`name(str)`会调用`string(const char *)`，`scores(pd, n)`将调用`ArrayDb(const double *, int)`。如果，省略初始化列表，将会调用对应类的默认构造函数。

注意，当初始化列表中包含多个成员时，它们被初始化的顺序为类中声明的顺序，而不是初始化列表中的顺序。

#### 2. 使用被包含对象的接口

被包含的对象的接口不是公有的，但是可以在类的方法中使用。例如`std::valarray`的`sum()`方法等。

## 14.2 私有继承

使用私有继承，基类的公有成员和保护成员都将成为派生类的私有成员，基类的公有方法将成为派生类的私有方法。私有继承和包含一样 ，获得实现，但不获得接口。

### 14.2.1 Student类示例（新版本）

上面的包含版本提供了两个显式命名的对象成员（`name`，`scores`），但是私有继承提供了两个无名称的子对象成员。

#### 1. 初始化基类组件

```C++
Student(const char * str, const double * pd, int n) : std::string(str), ArrayDb(pd, n) {}
```

可以看到和上面定义的不同之处。

```C++
// studenti.h
#ifndef C_PRIMER_STUDENTI_H
#define C_PRIMER_STUDENTI_H

#include <iostream>
#include <valarray>
#include <string>

class Student : private std::string, private std::valarray<double> {
private:
    typedef std::valarray<double> ArrayDb;
    std::ostream & arr_out(std::ostream & os) const;

public:
    Student() : std::string("Null Student"), ArrayDb() {}
    explicit Student(const std::string & s) 
        : std::string(s), ArrayDb() {}			// 注意这里和包含对象时的区别，下面也是
    explicit Student(int n) 
        : std::string("Nully"), ArrayDb(n) {}
    Student(const std::string & s, int n)
        : std::string(s), ArrayDb(n) {}
    Student(const std::string & s, const ArrayDb & a) 
        : std::string(s), ArrayDb(a) {}
    Student(const char *str, const double *pd, int n) 
        : std::string(s), ArrayDb(pd, n) {}
    ~Student(); {}
    double Average() const;
    double &operator[](int i);
    double operator[](int i) const;
    const std::string & Name() const;

    // friends
    friend std::istream &operator>>(std::istream & is, Student & stu);
    friend std::istream &getline(std::istream & is, Student & stu);
    friend std::ostream &operator<<(std::ostream & os, const Student & stu);
};

#endif //C_PRIMER_STUDENTI_H
```

#### 2. 访问基类的方法

使用私有继承时，只能在派生类方法中使用基类的方法。在前面的`Student::Average()`函数中，使用了数据成员来调用被包含对象的方法，如`scores.sum() / socres.size()`。在私有继承中，可以使用作用域解析运算符调用方法：

```C++
double Student::Average() const {
    if (ArrayDb::size() > 0)
        return ArrayDb::sum() / ArrayDb::size();
    else
        return 0;
}
```

#### 3. 访问基类对象

在私有继承中，可以访问基类的方法，如果要访问基类对象呢？在包含对象的版本中，可以通过`Name()`方法访问`string`对象`name`，在私有继承中，由于没有名称，不能直接访问，可以通过**强制类型转换**访问。

```C++
const string & Student::Name() const {
    return (const string &) *this;
}
```

上述方法将`Student`对象强制转换成`string`对象，并返回一个引用，指向继承于`string`类的对象。

#### 4. 访问基类的友元函数

和访问基类对象一样，由于没有数据成员，不能直接访问，可以通过强制转换来访问：

```C++
ostream & operator<<(ostream & os, const Student & stu) {
    os << "Scores for " << (const String &) stu << ":\n";
}
```

### 14.2.2 使用包含还是私有继承

通常，应该使用包含来建立has-a关系；如果新的类需要访问原有类的保护成员，或者需要重新定义虚函数，则应该使用私有继承。

### 14.2.3 保护继承

保护继承是私有继承的变体：

```C++
class Student : protected std::string, protected std::valarray<double> {};
```

使用保护继承，基类的公有成员和保护成员都成为派生类的保护成员，这样，在从派生类中派生出一个类时，第三代类将可以使用基类的接口，因为它在派生类中是保护成员，而不是私有的。私有继承则不能，因为从基类派生出来后，基类的公有方法在派生类中变成了私有方法。

下表总结了三种继承的特性

|       特征       |       公有继承       |       保护继承       |       私有继承       |
| :--------------: | :------------------: | :------------------: | :------------------: |
|   公有成员变成   |   派生类的公有成员   |   派生类的保护成员   |   派生类的私有成员   |
|   保护成员变成   |   派生类的保护成员   |   派生类的保护成员   |   派生类的私有成员   |
|   私有成员变成   | 只能通过基类接口访问 | 只能通过基类接口访问 | 只能通过基类接口访问 |
| 能否隐式向上转换 |          是          | 是（只能在派生类中） |          否          |

### 14.2.4 使用`using`重新定义访问权限

在使用保护派生或私有派生时，在派生类外部无法直接只用基类方法，如果需要这样做，有两种方法：

1. 在派生类中使用基类方法派生方法，将基类的方法包装在一个函数中，然后可以在外部调用

2. 使用`using`声明来包含基类方法：

   ```C++
   class Student : private std::string, private std::valarray<double> {
   public:
       using std::valarray<double>::min;
       using std::valarray<double>::max;
       ...
   };
   ```

   这样，在外部就可以直接使用基类的`min`和`max`方法：

   ```C++
   cout << "hight score: " << ada[i].max() << endl;
   ```

## 14.3 多重继承（Multiple Inheritance，MI）

MI出现的问题：

- 从两个不同的类中继承同名方法
- 从两个或更多个相关基类那里继承同一个类的多个实例

定义一个抽象基类`Worker`，然后从这个基类中派生出两个类：`Waiter`、`Singer`。然后从这两个派生类中再派生出一个`SingingWaiter`类，这种继承将导致上述出现的问题。

### 14.3.1 有多少Worker

假设从`Waiter`、`Singer`派生出了`SingingWaiter`类：

```C++
class SingingWaiter : public Singer, public Waiter {};
```

由于`Waiter`和`Singer`都继承了一个`Worker`组件，因此`SingingWaiter`将包含两个`Worker`组件。因为可以将基类指针指向派生类，这样就会出现二义性：

```C++
SingingWaiter = ed;
Worker * pw = &ed;			// 不知道这个Worker将转换成什么
```

因为`ed`中包含两个`Worker`对象，所以就会出现：

```C++
Worker * pw1 = (Waiter *) &ed;
Worker * pw2 = (Singer *) &ed;
```

解决这种问题，需要使用**虚基类**。

#### 1. 虚基类

为了避免包含两个`Worker`对象的拷贝，可以使用虚基类，在派生类声明中可以加入`virtual`关键字：

```C++
class Singer : virtual public Worker {};
class Waiter : public virtual Worker {}; 		// 前后次序无关紧要
```

#### 2. 新的构造函数规则

不使用虚基类时，构造函数在类间是可以传递的，也就是说下面的代码是合法的：

```C++
class A {
    int a;
public:
    A(int n = 0) : a(n) {}
};

class B {
    int b;
public:
    B(int m = 0, int n = 0) : A(n), b(m) {}
};

class C {
    int c;
public:
    C(int q = 0, int m = 0, int n = 0) : B(m, n), c(q) {}
};
```

C类只能使用B类的构造函数，B类使用A类的构造函数，这样，在构造C类的时候，传入的参数实际上是可以传递到A类的。但是在使用虚基类的时候：

```C++
SingingWaiter(const Worker & wk, int p = 0, int v = Singer::other) 
    	: Waiter(wk, p), Singer(wk, v) {}
```

上述定义中，如果构造`SingingWaiter`，传递`wk`的时候有两条路，会引起冲突。因为`Waiter`和`Singer`类都会调用`Worker`的构造函数。为了避免这种冲突，需要显式指定虚基类的构造函数：

```C++
SingingWaiter(const Worker & wk, int p = 0, int v = Singer::other) 
    	: Worker(wk), Waiter(wk, p), Singer(wk, v) {}
```

但是要注意，这种方法对于虚基类是合法的，而且是必须的，但是对于非虚基类，是非法的。

### 14.3.2 哪个方法

```C++
SingingWaiter newhire("Elise Hawks", 2005, 6, soprano);
newhire.Show()
```

上述对象继承于`Singer`和`Worker`，调用哪个`Show()`方法，是有二义性的。解决方法是在`SingingWaiter`中重新定义`Show()`方法。具体实现时可以使用模块化的方法：

```C++
void Worker::Data() const {
    cout << "Name: " << fullname << "\n";
    cout << "Employee ID: " << id << "\n";
}

void Waiter::Data() const {
    cout << "Panache rating: " << panache << "\n";
}

void Singer::Data() const {
    cout << "Vocal range: " << pv[voice] << "\n";
}

void SingingWaiter::Data() const {
    Singer::Data();
    Waiter::Data();
}

void SingingWaiter::Show() const {
    cout << "Category: singing waiter\n";
    Worker::Data();
    Data();
}
```

这样就避免了在定义`Show`方法时，不知道该使用哪个基类的`Show`方法的问题。

下面是改进后的`Student`类声明：

```C++
#ifndef C_PRIMER_WORKERMI_H
#define C_PRIMER_WORKERMI_H

#include <string>

class Worker {
private:
    std::string fullname;
    long id;

protected:
    virtual void Data() const;			// 模块化，用以在派生类中使用避免二义性
    virtual void Get();

public:
    Worker() : fullname("no one"), id(0L) {}
    Worker(const std::string & s, long n) : fullname(s), id(n) {}
    virtual ~Worker() = 0;
    virtual void Set() = 0;
    virtual void Show() const = 0;
};

class Waiter : virtual  public Worker {
private:
    int panache;

protected:
    void Data() const;
    void Get();

public:
    Waiter() : Worker(), panache(0) {}
    Waiter(const std::string & s, long n, int p = 0) : Worker(s, n), panache(p) {}
    Waiter(const Worker & wk, int p = 0) : Worker(wk), panache(p) {}
    void Set();
    void Show() const;
};

class Singer : virtual public Worker {
protected:
    enum {other, alto, contralto, soprano, bass, baritone, tenor};
    enum {Vtypes = 7};
    void Data() const;
    void Get();

private:
    static char *pv[Vtypes];
    int voice;

public:
    Singer() : Worker(), voice(other) {}
    Singer(const std::string & s, long n, int v = other)
            : Worker(s, n), voice(n) {}
    Singer(const Worker & wk, int v = other) 
            : Worker(wk), voice(v) {}

    void Set();
    void Show() const;
};


class SingingWaiter : public Singer, public Waiter {
protected:
    void Data() const;
    void Get();

public:
    // 注意下面构造函数的声明方式
    SingingWaiter() {}
    SingingWaiter(const std::string & s, long n, int p = 0, int v = other)
            : Worker(s, n), Waiter(s, n, p), Singer(s, n, v) {}
    SingingWaiter(const Worker & wk, int p = 0, int v = other)
            : Worker(wk), Waiter(wk, p), Singer(wk, v) {}
    SingingWaiter(const Waiter & wt, int v = other)
            : Worker(wt), Waiter(wt), Singer(wt, v) {}
    SingingWaiter(const Singer & wt, int p = 0)
            : Worker(wt), Waiter(wt, p), Singer(wt) {}
    void Set();
    void Show() const;
};
```

### 14.3.3 MI小结

MI会增加编程复杂度，但是这种复杂性主要是由于派生类通过多种途径继承同一个基类引起的。

## 14.4 类模板

Stack类和Queue类都是容器类，它们可以存储不同类型的对象，为了更方便的代码重用，可以定义类模板。在使用的时候可以方便的转换容器类的存储类型。

### 14.4.1 定义类模板

类的模板定义和函数模板类似。

```C++
#ifndef C_PRIMER_STACKTP_H
#define C_PRIMER_STACKTP_H

template <class Type>
class Stack {
private:
    enum {MAX = 10};
    Type items[MAX];
    int top;

public:
    Stack();
    bool isempty();
    bool isfull();
    bool push(const Type & item);
    bool pop(Type & item);
};

template <class Type>
Stack<Type>::Stack() {
    top = 0;
}

template <class Type>
bool Stack<Type>::isempty() {
    return top == 0;
}

template <class Type>
bool Stack<Type>::isfull() {
    return top == MAX;
}

template <class Type>
bool Stack<Type>::push(const Type & item) {
    if (top < MAX) {
        items[top++] = item;
        return true;
    }
    else
        return false;
}

template <class Type>
bool Stack<Type>::pop(Type & item) {
    if (top > 0) {
        item = items[--top];
        return true;
    }
    else
        return false;
}

#endif //C_PRIMER_STACKTP_H
```

### 14.4.2 使用模板类

```C++
Stack<int> kernels;					// Stack类存储int
Stack<std::string> colonels;		// Stack类存储string
```

### 14.4.3 深入探讨模板类

可以使用内置类型和类对象作为类模板的类型。指针也可以，但是会带来一些问题。

#### 1. 不正确的使用指针栈

以正确的`Stack<Type>`为基础：`Stack<char *> st;`，创建一个指针栈。

**版本1**：

​	将`string po`替换为`char * po`。

​	这个方法仅仅创建指针，没有分配内存空间。在写ADT_Test程序时，这种错误出现的很多，有把指针复制到`nullptr`上的问题。程序会通过编译，但是在将输入或者赋值保存在不适合的内存单元中时会崩溃。

**版本2**：

​	将`string po`替换为`char po[40]`。

​	这为输入的字符串提供了空间，而且`po`的类型为`char *`，可以放在栈中，但是数组和`Stack`类的`pop`方法冲突：

```C++
template <class Type>
bool Stack<Type>::pop(Type & item) {
	if (top > 0) {
		item = items[--top];
		return true;
	}
	else
		return false;
}
```

引用变量`item`必须引用某种类型的左值，而不能是数组名。其次，即使`item`可以引用数组，也不能给数组名赋值，因为数组名为指针。

**版本3**：

​	将`string po`替换为`char *po = new char[40]`

​	这种方法分配了内存空间，`po`也是变量，和`pop()`兼容。但是只有一个`po`变量，指向相同的内存地址，每次入栈的地址都是相同的，这没有任何意义。

#### 2. 正确使用指针栈

方法之一是：让调用程序创建指针数组，每个指针都指向不同的字符串。栈只负责管理指针，不负责创建指针。把字符串压入栈实际上是新建一个指向该字符串的指针，即创建一个新的指针，指针的值是现有字符串的地址。析构函数调用的时候是删除保存指针的数组，而不会删除数组元素指向的字符串。

### 14.4.4 数组模板示例和非类型参数

使用模板参数提供数组大小的数组模板示例：

```C++
#ifndef C_PRIMER_ARRAYTP_H
#define C_PRIMER_ARRAYTP_H

#include <iostream>
#include <cstdlib>

// 传入模板参数n
template <class T, int n>
class ArrayTP {
private:
    T ar[n];

public:
    ArrayTP() {};
    explicit ArrayTP(const T & v);
    virtual T &operator[](int i);
    virtual T operator[](int i) const;
};

template <class T, int n>
ArrayTP<T, n>::ArrayTP(const T &v) {
    for (int i = 0; i < n; i++)
        ar[i] = v;
}

template <class T, int n>
T& ArrayTP<T, n>::operator[](int i) {
    if (i < 0 || i >= n) {
        std::cerr << "Error in array limits: " << i
                  << " is out of range\n";
        std::exit(EXIT_FAILURE);
    }
    return ar[i];
}

template <class T, int n>
T ArrayTP<T, n>::operator[](int i) const {
    if (i < 0 || i >= n) {
        std::cerr << "Error in array limits: " << i
                  << " is out of range\n";
        std::exit(EXIT_FAILURE);
    }
    return ar[i];
}

#endif //C_PRIMER_ARRAYTP_H
```

像上面`template <class T, int n>`中，`n`这种参数成为非类型参数或表达式参数。可以是整型、枚举、引用或指针。所以`double m`是非法的，但`double *pm`是合法的。模板代码不能修改参数的值，也不能使用其地址。在实例化模板时，参数值必须是常量，所以不能传递。

### 14.4.5 模板多功能性

#### 1. 递归使用模板

```C++
ArrayTP< ArrayTP<int , 5>, 10> twodee;
int twodee[10][5];						// 第一行的等价声明
```

#### 2. 使用多个类型参数

```C++
#include <iostream>
#include <string>

template <class T1, class T2>
class Pair {
private:
    T1 a;
    T2 b;
public:
    T1 & first();
    T2 & second();
    T1 first() const { return a; }
    T2 second() const { return b; }
    Pair(const T1 & aval, const T2 & bval) : a(aval), b(bval) {}
    Pair() {}
};

template <class T1, class T2>
T1 & Pair<T1, T2>::first() {
    return a;
}

template <class T1, class T2>
T2 & Pair<T1, T2>::second() {
    return b;
}


int main()
{
    using std::cout;
    using std::endl;
    using std::string;
    Pair<string, int> ratings[4] = {
            Pair<string, int>("The Purpled Duck", 5),
            Pair<string, int>("Jaquie's Frisco Al Fresco", 4),
            Pair<string, int>("Cafe Souffle", 5),
            Pair<string, int>("Bertie's Eats", 3)
    };
    int joints = sizeof(ratings) / sizeof(Pair<string, int>);
    cout << "Rating:\t Eatery\n";
    for (int i = 0; i < joints; i++)
        cout << ratings[i].second() << ":\t"
             << ratings[i].first() << endl;
    cout << "Oops! Revised rating:\n";
    ratings[3].first() = "Bertie's Fab Eats";
    ratings[3].second() = 6;
    cout << ratings[3].second() << ":\t"
         << ratings[3].first() << endl;

    return 0;
}
```

#### 3. 默认类型模板参数

可以为模板参数提供默认值：

```C++
template <class T1, class T2 = int>
```

### 14.4.6 模板的具体化

类模板可以隐式实例化、显式实例化、显式具体化，统称为具体化。

#### 1. 隐式实例化

```C++
ArrayTP<int, 100> stuff;			// 隐式实例化
```

#### 2. 显式实例化

当使用关键字`template`并指出所需类型来声明类的时候，将生成类声明的显式实例化。

```C++
template class ArrayTP<string, 100>;		// 显式实例化
```

#### 3. 显式具体化

有时可能需要在为特殊类型实例化时，对模板的行为进行修改。这是可以创建具体化。例如，已经定义了一个表示排序后的数组的模板类：

```C++
template <typename T>
class SortedArray {};
```

假设其中定义的比较大小的方法为`operator<()`，这对整型和`double`是可以用的，但是如果用在字符串上显然不行。这时，可以提供一个具体化的模板，专门给`const char *`使用：

```C++
template <> class SortedArray<const char char *> {};
```

在这个模板中，将使用`strcmp`来比较字符串。

当请求`const char *`类型的模板时，使用的是后面的专有定义：

```C++
SortedArray<int> scores;			// 使用通用模板定义
SortedArray<const char *> dates;	// 使用专有模板定义
```

#### 4. 部分具体化

### 14.4.7 成员模板

```C++
#include <iostream>
using std::cout;
using std::endl;

template <typename T>
class beta {
private:
    template <typename V>				// 嵌套的成员模板类
    class hold {
    private:
        V val;
    public:
        hold(V v = 0) : val(v) {}
        void show() const { cout << val << endl; }
        V Value() const { return val; }
    };
    hold<T> q;
    hold<int> n;

public:
    beta(T t, int i) : q(t), n(i) {}
    template <typename U>
    U blab(U u, T t) { return (n.Value() + q.Value()) * u / t; }
    void Show() const { q.show(); n.show(); }
};

int main()
{
    beta<double> guy(3.5, 3);
    cout << "T was set to double\n";
    guy.Show();
    cout << "V was set to T, which is double, then V was set ot int\n";
    cout << guy.blab(10, 2.3) << endl;
    cout << "U was set to int\n";
    cout << guy.blab(10.0, 2.3) << endl;
    cout << "U was set to double\n";
    cout << "Done.\n";

    return 0;
}
```

### 14.4.8 将模板用做参数

```C++
template <template <typename T> class Thing>
class Crab
```

其中，模板的参数是`template <typename T>class Thing`，`template <typename T>class`是类型，`Thing`是参数。意味着如果有这样的声明：`Crab<King> legs;`，那么`King`就是一个模板类。

### 14.4.9 模板类和友元

模板类声明也可以有友元，分三类：

- 非模板友元；
- 约束模板友元，友元类型取决于类被实例化时的类型；
- 非约束模板友元，友元的所有具体化都是类的每个具体化的友元。

#### 1. 模板类的非模板友元

```C++
template <class T>
class HasFriend {
    friend void report(HasFriend<T> &);
}
```

由于`report`本身并不是模板函数，而只是使用一个模板做参数，所以必须要为使用的友元定义显示具体化：

```C++
void report(HasFriend<short> &) {};
void report(HasFriend<int> &) {};
```

#### 2. 模板类的约束模板友元函数

```C++
#include <iostream>
using namespace std;

// 在类声明之前声明友元函数
template <typename T> void counts();
template <typename T> void report(T &);

// 然后在类中声明友元函数
template <typename TT>
class HasFriendT {
private:
    TT item;
    static int ct;
public:
    HasFriendT(const TT & i) : item(i) {ct++;}
    ~HasFriendT() {ct--;}
    // 因为counts没有参数，必须使用<TT>来指明具体化
    friend void counts<TT>();
    // report有参数HasFriendT<TT> &，所以不需要显式指定具体化
    friend void report<>(HasFriendT<TT> &);
};

template <typename T>
int HasFriendT<T>::ct = 0;

template <typename T>
void counts() {
    cout << "template size: " << sizeof(HasFriendT<T>) << "; ";
    cout << "template counts(): " << HasFriendT<T>::ct << endl;
}

template <typename T>
void report(T & hf) {
    cout << hf.item << endl;
}

int main()
{
    counts<int>();
    HasFriendT<int> hfi1(10);
    HasFriendT<int> hfi2(20);
    HasFriendT<double> hfdb(10.5);
    report(hfi1);
    report(hfi2);
    report(hfdb);
    cout << "counts<int>() output: \n";
    counts<int>();
    cout << "counts<double>() output:\n";
    counts<double>();

    return 0;
}
```

#### 3. 模板类的非约束模板友元函数

前面是在类外声明的的模板友元，通过在类内部声明模板友元，可以创建非约束的模板函数。

```c++
#include <iostream>
using namespace std;

template <typename T>
class ManyFriend {
private:
    T item;
public:
    ManyFriend(const T & i) : item(i) {}
    template <typename C, typename D> friend void show2(C &, D &);
};

template <typename C, typename D> void show2(C &c, D &d) {
    cout << c.item <<", " << d.item << endl;
}

int main()
{   
    ManyFriend<int> hfi1(10);
    ManyFriend<int> hfi2(20);
    ManyFriend<double> hfdb(10.5);
    cout << "hfi1, hfi2: ";
    show2(hfi1, hfi2);
    cout << "hfdb, hfi2: ";
    show2(hfdb, hfi2);

    return 0;
}
```

### 14.4.10 模板别名

可以为模板类制定别名，使用`typedef`：

```C++
// 老式做法
typedef std::array<double, 12> arrd;
typedef std::array<int, 12> arri;

// C++11新增
template<typename T>
using arrtype = std::array<T, 12>;

arrtype<double> gallons;
arrtype<int> days;
```

也可以将`using=`用于非模板，用于非模板时，与常规的`typedef`等价：

```C++
typedef const char * pc1;
using pc2 = const char *;
```

