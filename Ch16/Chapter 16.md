[TOC]

# Chapter 16. string类和标准模板库

- 标准C++string类
- 模板`auto_ptr`、`unique_ptr`和`shared_ptr`
- 标准模板库（STL）
- 容器类
- 迭代器
- 函数对象（functor)
- STL算法
- 模板`initializer_list`

## 16.1 string类

### 16.1.1 构造字符串

`string`实际上是模板具体化`basic_string<char>`的一个`typedef`，同时省略了内存管理的相关参数。`string`类将`string::nops`定义为字符串最大长度，通常为`unsigned int`的最大值。另外NBTS代表以空字符结束的字符串——C风格的字符串。

```C++
#include <iostream>
#include <string>

int main()
{
    using namespace std;
    string one("Lottery Winner!");
    cout << one << endl;
    string two(20, '$');
    cout << two << endl;
    string three(one);
    cout << three << endl;
    one += " Oops!";
    cout << one << endl;
    two = "Sorry! That was ";
    three[0] = 'P';
    string four;
    four = two + three;
    cout << four << endl;
    char alls[] = "All's well that ends well";
    string five(alls, 20);
    cout << five << "!\n";
    string six(alls + 6, alls + 10);		// 从alls第6个字符到第10个字符截断
    cout << six << ", ";
    string seven(&five[6], &five[10]);
    cout << seven << "...\n";
    string eight(four, 7, 16);
    cout << eight << " in motion!" << endl;

    return 0;
}

/* 输出示例
Lottery Winner!
$$$$$$$$$$$$$$$$$$$$
Lottery Winner!
Lottery Winner! Oops!
Sorry! That was Pottery Winner!
All's well that ends!
well, well...
That was Pottery in motion!
*/
```

### 16.1.2 string类输入

对于C风格字符串：

```C++
char info[100];
cin >> info; 			// 读入单个单词，空格处停止
cin.getline(info, 100)	// 读入一行，抛弃 \n
cin.get(info, 100)		// 读入一行，将 \n 保留在输入队列中    
```

对于`string`对象：

```C++
string stuff;
cin >> stuff;			// 读入单个单词，空格处停止
getline(cin, stuff);	// 读入一行，抛弃 \n
```

`string`版本的`getline`函数可以自动调整读取长度。

**两个限制因素**：第一个是`string`对象的最大允许长度，由常量`string::npos`指定，通常为最大的`unsigned int`。第二个限制因素是程序可以使用的内存量。

### 16.1.3 使用字符串

字符串比较（使用重载的关系运算符），字符串查找（单字符、子串）。

### 16.1.4 string还提供了哪些功能

删除字符串部分或全部内容、部分替换、插入或删除数据、部分内容比较、提取子串、复制子串、交换子串等。

### 16.1.5 字符串种类

string库实际上是一个模板类：

```C++
template<class charT, class traits = char _traits<charT>,
		 class Allocator = allocator<charT> >
basic_string {...};
```

有4个模板具体化：

```C++
typedef basic_string<char> string;
typedef basic_string<wchar_t> wstring;
typedef basic_string<char16_t> u16string;
typedef basic_string<char32_t> u32string;
```

## 16.2 智能指针模板类

智能指针类似于常规指针的功能，但是它可以自动释放指针指向的内存，也就是说它里面包含了析构函数，可以实现内存的自动管理。C++中有三种智能指针：

- `auto_ptr`
- `unique_ptr`
- `shared_ptr`

### 16.2.1 使用智能指针

可以使用`new`运算符来把地址赋给这种指针对象，当智能指针过期时，其析构函数将会自动释放指向的内存。智能指针的定义包含在头文件`memory`中：

```C++
template<class X> class auto_ptr {
public:
    explicit auto_ptr(X * p = 0) throw(); 
}

auto_ptr<double> pd(new double);			// 声明一个指向double内存块的指针
auto_ptr<string> ps(new string);
```

普通指针不能隐式转换成智能指针，只能显式转换：

```C++
shared_ptr<double> pd;
double * p_reg = new double;
pd = p_reg;								// 不可以，不能隐式转换
pd = shared_ptr<double>(p_reg);			// 可以，显式转换
shared_ptr<double> pshared = p_reg;		// 不可以
shared_ptr<double> pshared(p_reg);		// 可以
```

### 16.2.2 有关智能指针的注意事项

```C++
auto_ptr<string> ps (new string("I reigned lonely as cloud."));
auto_ptr<string> vocation;
vocation = ps;
```

上述代码中，`vocation`和`ps`指向了同一个string对象，这导致程序试图删除同一个对象两次。为了解决这个问题：

- 定义赋值运算符，使用深复制
- 建立所有权的概念，对于特定的对象，只有一个智能指针可以拥有它，只有该智能指针可以删除对象。赋值操作转让所有权，这是`unique_ptr`和`auto_ptr`的做法，不过`unique_ptr`更严格。
- 创建智能更高的指针，跟踪引用特定对象的智能指针数，称为引用计数。赋值时，计数加1，过期时，计数减1。这是`shared_ptr`采用的策略。

### 16.2.3 `unique_ptr`为何优于`auto_ptr`

为了避免转让所有权后继续使用原来的指针，`unique_ptr`将不允许使用赋值语句：

```C++
unique_ptr<string> p3 (new string("auto"));
unique_ptr<string> p4;
p4 = p3;				// 非法，p3不再指向有效数据
```

但是上述语句对于`auto_ptr`却是合法的。

`unique_ptr`还可以用于数组的变体。

### 16.2.4 选择智能指针

如果程序需要多个指向同一对象的指针，应该使用`shared_ptr`，否则应该使用`unique_ptr`。

## 16.3 标准模板库（STL）

STL提供了一组表示容器、迭代器、函数对象和算法的模板。迭代器能够用来遍历容器的对象，与能够遍历数组的指针类似，是广义指针；函数对象是类似于函数的对象，可以是类对象或函数指针。

### 16.3.1 模板类`vector`

这里`vector`代表着数组。

### 16.3.2 可对矢量执行的操作

`size()`——返回元素数目、`swap()`——交换内容、`begin()`——返回一个指向容器中第一个元素的迭代器、`end()`——返回一个表示超过容器尾的迭代器。迭代器是一个广义指针，可以是指针，也可以是一个可对其执行类似指针操作的对象（解引用，递增）。

STL中每个容器类都定义了一个合适的迭代器，该迭代器的类型是一个名为iterator的typedef：

```C++
vector<double>::iterator pd;
vector<double> scores;

pd = scores.begin();
*pd = 22.3;
++pd;
```

如上，迭代器的行为就像指针。可以使用它来遍历容器：

```C++
for (pd = scores.begin(); pd != scores.end(); pd++)
    cout << *pd << endl;
```

所有容器都包含这些方法。`vector`模板类也包含一些只有某些STL容器才有的方法，例如`push_back()`。它将元素添加到矢量的末尾。这样做时，它负责内存管理，增加矢量的长度。

`erase()`方法可以删除矢量给定区间的元素。

```C++
scores.erase(scores.begin(), scores.begin() + 2);	// 删除begin和begin+1指向的元素
```

`insert()`方法和`erase()`方法相反，向指定位置插入元素。