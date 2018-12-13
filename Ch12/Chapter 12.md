[TOC]

# Chapter 12. 类和动态内存分配

- 对类成员使用动态内存分配
- 隐式和显式复制构造函数
- 隐式和显式重载赋值运算符
- 在构造函数中使用new所必须完成的工作
- 使用静态类成员
- 将定位new运算符用于对象
- 使用指向对象的指针
- 实现队列抽象数据类型（ADT）

## 12.1 动态内存和类

### 12.1.1 静态类成员

```C++
#ifndef STRINGBAD_H
#define STRINGBAD_H

#include <iosfwd>

class StringBad {
private:
    char * str;
    int len;
    static int num_string;

public:
    StringBad(const char * s);
    StringBad();
    ~StringBad();

    friend std::ostream &operator<<(std::ostream & os, const StringBad & st);
};

#endif // STRINGBAD_H
```

其中`num_string`就是一个静态类成员，无论创建多少对象，只创建一个静态类成员的副本。也就是说，如果声明了10个`StringBad`类的对象，将有10个`str`和`len`成员，但是只有一个`num_string`。借助这种特性，可以记录创建的对象数目。静态类成员的初始化：

```C++
// stringbad.cpp
int StringBad::num_string = 0;
```

静态类成员不能在类声明时初始化，声明并不会给变量分配内存。

当使用一个对象来初始化另一个对象时，调用的构造函数应该如下：

```C++
StringBad sailor = sports;		// 等同于下面的语句
StringBad sailor = StringBad(sports);		// 它调用了下面的构造函数
StringBad(const StringBad &);
```

由于没有给出上述构造函数，编译器会自动生成（成为复制构造函数），这样就会导致一些问题。

### 12.1.2 特殊成员函数

C++自动提供的成员函数：

- 默认构造函数，如果没有定义构造函数
- 默认析构函数，如果没有定义
- 复制构造函数，如果没有定义
- 赋值运算符，如果没有定义
- 地址运算符，如果没有定义

#### 1. 默认构造函数

如果没有定义任何构造函数，编译器会自动提供一个不带任何参数的空函数作为构造函数：

```C++
Klunk::Klunk() {}
```

#### 2. 复制构造函数

复制构造函数用于将一个对象复制到新对象中：

```C++
Class_name(const Class_name &);
```

#### 3. 何时调用复制构造函数

新建一个对象，并将其初始化为一个现有对象时，会调用复制构造函数：

```C++
StringBad ditto(motto);
StringBad metoo = motto;
StringBad also = StringBad(motto);
StringBad * pStringBad = new StringBad(motto);
```

其次，每当程序生成对象副本时也会调用复制构造函数。例如，按值传递对象时，需要创建对象副本，这时会使用复制构造函数。

#### 4. 默认的复制构造函数功能

默认的复制构造函数逐个复制非静态成员到新对象，复制的是成员的值：

```C++
StringBad sailor = sports;			// 和下面语句等效

StringBad sailor;					// 和上面等效，但是由于不允许访问私有成员，无法编译
sailor.str = sports.str;	
sailor.len = sports.len;
```

### 12.1.3 复制构造函数的问题

隐式的复制构造函数是按值复制的，例如：

```C++
sailor.str = sports.str;
```

这里复制的并不是字符串，而是字符串地址，这两个指针指向了同一字符串，当析构函数被调用时，首先释放`sailor.str`，这时，`sports.str`指向的字符串已经被释放了，但是对象本身仍然存在，析构函数会继续释放`sports.str`，这样就会导致内存的多次释放，出现异常问题。

解决方法就是定义一个显式的复制构造函数：

```C++
StringBad::StringBad(const StringBad & st) {
    num_string++;
    len = st.len;
    str = new char [len + 1];
    std::strcpy(str, st.str);
}
```

这样就不是只复制地址给新对象，而是创建一个新的副本，就不会导致内存多次释放的问题。这也叫深拷贝。

必须定义复制构造函数的原因在于，有一些类成员是使用new初始化的、指向数据的指针，而不是数据本身。

### 12.1.4 赋值运算符的问题

在C++中允许类对象赋值，这是通过重载赋值运算符实现的：

```C++
Class_name & Class_name::operator=(const Class_name &);
```

#### 1. 何时使用赋值运算符

当将一个已有的对象赋值给理你个一个对象时，会使用赋值运算符。初始化对象不一定会。

#### 2. 赋值运算符的问题

和复制构造函数的问题一样，使用赋值运算符时，也是浅拷贝。只是传地址，而不是创建新的副本，会导致内存多次释放。

#### 3. 解决问题

解决方法是重载赋值运算符`=`，单独提供重载函数：

```C++
StringBad & StringBad::operator=(const StringBad & st) {
    if (this == &st)
        return *this;		// 对象指向自身，什么都不做
    delete [] str;
    len = st.len;
    str = new char [len + 1];
    std::strcpy(str, st.str);
    return *this;
}
```

- 首先，目标函数可能使用了未释放的私有成员`str`，要先使用`delete`释放。
- 然后还要检查是否为自我复制，如果传递的字符串和当前对象相同，就什么都不做。

## 12.2 新的String类

### 12.2.1 修改后的默认构造函数

```C++
String::String() {
    len = 0;
    str = new char[1];
    str[0] = '\0';
}
// 也可以是
String::String() {
    len = 0;
    str = nullptr;		// C++11中引进的新关键字，代表空指针
}
```

### 12.2.2 比较成员函数

```C++
bool operator<(const String &s1, const String &s2) {
    return (std::strcmp(st1.str, st2.str) < 0);
}
```

### 12.2.3 使用中括号访问字符

可以重载`[]`，来实现访问字符串字符：

```C++
char & String::operator[](int i) {
    return str[i];
}
```

但是上面这种声明不适合`const`字符串，因为它无法保证不修改数据。可以另外提供一个常量版本：

```C++
const char & String::operator[](int i) const {
    return str[i];
}
```

### 12.2.4 静态类成员函数

可以将成员函数声明为静态的：

```C++
static int Howmany() { return num_string; }
```

- 静态成员函数不能通过对象调用，也不能使用`this`指针，如果它是在共有部分被声明的，可以使用类名和作用域解析运算符`::`来使用：`int count = String::Howmany();`。
- 静态成员函数不能和对象关联，只能使用静态的数据成员。

### 12.2.5 进一步重载赋值运算符

前面重载赋值运算符时，可以将两个`String`对象相互复制，但是如果要使用常规字符串复制就不行，所以需要进一步重载：

```C++
String & String::operator=(const char * s) {
    delete [] str;
    len = std::strlen(s);
    str = new char[len + 1];
    std::strcpy(str, s);
    return *this;
}
```

## 12.3 在构造函数中使用new时应注意的事项

### 12.3.1 应该和不应该

```C++
String::String() {			// 没有使用new，在使用delete释放的时候会出现不可预测的问题
	str = "default string";
    len = std::strlen(str);
}

String::String(const char *s) {
    len = std::strlen(s);
    str = new char;			// 使用了非配套的new，后面使用delete []的时候也不正确
    std::strcpy(str, s);
}
```

### 12.3.2 包含类成员的类的逐成员复制

```C++
class Magazine {
private:
    String title;
    String publisher;
}
```

在这里，是不需要为`Magazine`类单独编写复制构造函数和复制运算符的，因为`String`类中已经有了相关实现。但是，如果要为`Magazine`类的其他成员定义复制构造函数和赋值运算符，必须显式调用`String`的复制构造函数和赋值运算符。

## 12.4 有关返回对象的说明

返回指向对象的引用、指向对象的`const`引用、`const`对象。

### 12.4.1 返回指向`const`对象的引用

要返回`Vector`对象较大的，有两种方法，一是返回对象，二是返回对象引用：

```C++
const Vector Max(const Vector & v1, const Vector & v2) {	// 返回对象
    return (v1.magval() > v2.magval() ? v1 : v2);
}

const Vector & Max(const Vector & v1, const Vector & v2) {	// 返回引用
    return (v1.magval() > v2.magval() ? v1 : v2);
}
```

返回对象将调用复制构造函数，返回引用不会。

### 12.4.2 返回指向非`const`对象的引用

重载赋值运算符以及重载`<<`运算符需要使用返回非`const`的引用。

### 12.4.3 返回对象

如果对象是被调函数的局部变量，不能返回引用，而应该返回对象，通常重载算术运算符属于这一类。

### 12.4.4 返回`const`对象

## 12.5 使用指向对象的指针

### 12.5.1 `new`和`delete`

- 如果对象是动态变量，则当执行完定义该对象的程序块，将调用析构函数。
- 如果对象是用`new`创建的，则仅当显式使用`delete`删除对象时，才会调用析构函数

### 12.5.2 指针和对象小结

### 12.5.3 定位`new`运算符

程序员必须负责管理使用定位`new`运算符分配的内存单元。定位`new`运算符就创建的变量不能直接使用`delete`删除，要使用`delete`删除分配的buffer：

```C++
char * buffer = new char[BUF];

JustTesting *pc1;
pc1 = new (buffer) JustTesting("Bad Idea", 6);

delete pc1;			// 错误，不能这么做
delete [] buffer; 	// 正确的做法
```

上面这样释放的仅仅是buffer的内存单元，对于对象`pc1`来说，还必须显式调用析构函数来销毁对象：

```C++
pc1->~JustTesting();
```

## 12.7 队列模拟

### 12.7.1 队列类

```C++
class Queue {
    enum {Q_SIZE = 10};
private:
public:
    Queue(int qs = Q_SIZE);
    ~Queue();
    bool isempty() const;
    bool isfull() const;
    int queuecount() const;
    bool enqueue(const Item &item);
    bool dequeue(Item &item);
};
```

#### 1. Queue类的实现

使用链表，类中嵌套结构声明：

```C++
class Queue {
    private:
    	struct Node {Item item; struct Node * next;};
    	enum {Q_SIZE = 10};
    public:
    	Node * front;
    	Node * rear;
    	int items;
    	const int qsize;
}
```

#### 2. 类方法

要使用类的构造函数给类成员赋值，但是，不能给`qsize`赋值，因为它是常量，可以初始化，但不能赋值。使用成员初始化列表可以在执行构造函数体之前进行初始化：

```C++
Queue::Queue(int qs) : qsize(qs) {
    front = rear = nullptr;
    items = 0;
}
```

对`const`类成员必须使用这种语法，被声明为引用的类的成员也必须使用这种语法：

```C++
class Agency {...};
class Agent {
    private:
    	Agency & belong;
}
Agent::Agent(Agency & a) : belong(a) {...}
```

- 这种初始化方法只能用于构造函数
- 必须使用这种格式来初始化非静态`const`数据成员
- 必须使用这种格式初始化引用数据成员

### 12.7.2 Customer类

需要知道客户的到达时间和随机的交易时长，当客户到达队首时，记录时间，得到等待时间。