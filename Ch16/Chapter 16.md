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

### 16.3.3 对矢量可执行的其他操作

- `for_each()`接收三个参数，前两个是定义容器中区间的迭代器，最后一个是指向函数的指针：

  ```C++
  vector<Review>::iterator pr;
  for (pr = books.begin(); pr != books.end(); pr++)
      ShowReview(*pr);
  // 替换为for_each
  for_each(books.begin(), books.end(), ShowReview);
  ```

- `random_shuffle()`函数接收两个指定区间的迭代器参数，并随机排列该区间中的元素。

- `sort()`函数要求容器支持随机访问。有两个版本，一个接收两个区间参数，然后排序。另一个接收三个参数，前两个是区间参数，最后一个是函数指针。

### 16.3.4 基于范围的for循环（C++11）

```C++
for_each(books.begin(), books.end(), ShowReview);

// 替换为
for (auto x : books) ShowReview(x);

// 如果希望修改x
for (auto & x : books) ShowReview(x);
```

## 16.4 泛型编程

STL是一种泛型编程（generic programming）。泛型编程关注的是算法，它旨在编写独立于数据类型的代码，在C++中通过模板实现。

### 16.4.1 为何使用迭代器

模板使得算法独立于数据的存储类型，而迭代器使得算法独立于使用的容器类型，它独立于容器本身的数据结构。模板提供了存储在容器中的数据类型的通用表示，而迭代器提供了容器中的值的通用表示。

STL中每个容器类（`vector`、`list`、`deque`等）都有相应的迭代器类型，其中提供了必要的操作（*和++等）。其次，每个容器类都有一个超尾标记，当迭代器递增到超越容器的最后一个值后，这个值将被赋值给迭代器。

- 应该能对迭代器进行解引用操作，`*p`
- 应该能够将一个迭代器赋给另一个，即如果p，q都是迭代器，应该定义`p = q`操作
- 应该能够对两个迭代器进行比较，即要定义`==`和`!=`操作
- 应该能够使用迭代器遍历容器中元素，需要定义`++p`和`p++`操作

STL方法，首先是处理容器的算法，应尽可能用通用的术语来表达算法，使之独立于数据类型和容器类型。为使通用算法能够适用于具体情况，应定义能够满足算法需求的迭代器，并把要求加到容器设计上。即基于算法的要求，设计基本迭代器的特征和容器特征。

### 16.4.2 迭代器类型

STL定义了5中迭代器类型，输入迭代器、输出迭代器、正向迭代器、双向迭代器和随机访问迭代器。

```c++
template<class InputIterator, class T>
// 输入迭代器    
InputIterator find (InputIterator first, InputIterator last, const T& value);     

template<class RandomAccessIterator>
// 随机访问迭代器
void sort(RandomAccessIterator first, RandomAccessIterator last);
```

#### 1. 输入迭代器

对输入迭代器解引用将使程序能够读取容器中的值，但不一定能让程序修改值。输入迭代器必须能够访问容器中所有的值，可通过`++`实现。输入迭代器是单向迭代器，只能递增，不能倒退。

#### 2. 输出迭代器

输出迭代器只能通过解引用修改容器值，但不能读取，类似于`cout`，只能发送显示，却不能读取。简而言之，对单通行、只读算法，可以使用输入迭代器；对于单通行、只写算法，则可以使用输出迭代器。

#### 3. 正向迭代器

正向迭代器只使用`++`来遍历容器，它按相同顺序遍历一系列值，将正向迭代器递增后，仍然可以访问前面的值。

#### 4. 双向迭代器

假设算法需要双向遍历容器，例如将列表反转，就可以使用双向迭代器。双向迭代器具有正向迭代器的所有特性。

#### 5. 随机访问迭代器

随机访问迭代器具有双向迭代器的所有特性，同时添加了随机访问的操作。

### 16.4.3 迭代器的层次结构

从上面的叙述中，可以看到迭代器具有层次结构，正向迭代器具有输入输出迭代器的所有功能，同时有自己的功能，双向迭代器具有正向迭代器的全部功能，随机访问迭代器具有双向迭代器的所有功能。

### 16.4.4 概念、改进和模型

在C++中，上述的迭代器是一系列要求，而不是类似于`int`等的一种类型，把这种要求称为**概念**。双向迭代器继承了正向迭代器的所有功能，但这又不是普通意义上的继承，是一种概念上的继承，称为**改进**。概念的具体实现被称为**模型**。

#### 1. 将指针用作迭代器

迭代器是广义指针，而指针满足所有的迭代器要求。STL预定义的迭代器：`ostream_iterator`、`istream_iterator`等。

#### 2. 其他有用的迭代器

除了`ostream_iterator`和`istream_iterator`之外，还有一些预定义的迭代器`reverse_iterator`、`back_insert_iterator`、`front_insert_iterator`和`insert_iterator`。

```C++
#include <iostream>
#include <iterator>
#include <vector>

int main()
{
    using namespace std;

    int casts[10] = {6, 7, 2, 9, 4, 11, 8, 7, 10, 5};
    vector<int> dice(10);
    copy(casts, casts+10, dice.begin());
    cout << "Let the dice be cast!\n";
    ostream_iterator<int, char> out_iter(cout, " ");
    copy(dice.begin(), dice.end(), out_iter);
    cout << endl;
    cout << "Implicit use of reverse iterator.\n";
    copy(dice.rbegin(), dice.rend(), out_iter);
    cout << endl;
    cout << "Explicit use of reverse iterator.\n";
    vector<int>::reverse_iterator ri;
    for (ri = dice.rbegin(); ri != dice.rend(); ++ri)
        cout << *ri << ' ';
    cout << endl;

    return 0;
}

/* 输出示例
Let the dice be cast!
6 7 2 9 4 11 8 7 10 5 
Implicit use of reverse iterator.
5 10 7 8 11 4 9 2 7 6 
Explicit use of reverse iterator.
5 10 7 8 11 4 9 2 7 6 
*/
```

反向指针`dice.rbegin()`指向超尾，不能直接对其解引用，需要先递减，然后解引用。

`back_insert_iterator`将元素插入到容器尾部，`fron_insert_iterator`将元素插入到容器前端，`insert_iterator`将元素插入到指定位置的前面。

```C++
#include <iostream>
#include <string>
#include <algorithm>
#include <iterator>
#include <vector>

void output(const std::string & s) {std::cout << s << " ";}

int main()
{
    using namespace std;
    string s1[4] = {"fine", "fish", "fashion", "fate"};
    string s2[2] = {"busy", "bats"};
    string s3[2] = {"silly", "singers"};
    vector<string> words(4);
    copy(s1, s1+4, words.begin());
    for_each(words.begin(), words.end(), output);
    cout << endl;
    // 将s2后面的两个元素复制到后插迭代器中，即插入到words后面
    copy(s2, s2+2, back_insert_iterator<vector<string>> (words));
    for_each(words.begin(), words.end(), output);
    cout << endl;

    copy(s3, s3+2, insert_iterator<vector<string>> (words, words.begin()));
    for_each(words.begin(), words.end(), output);
    cout << endl;

    return 0;
}

/* 输出示例
fine fish fashion fate 
fine fish fashion fate busy bats 
silly singers fine fish fashion fate busy bats 
*/
```

### 16.4.5 容器种类

`deque、list、queue、priority_queue、stack、vector、map、multimap、set、multiset、forward_list、unordered_map、unordered_multimap、unordered_set和unordered_multiset`.

#### 1. 容器概念

容器概念指定了所有STL容器类都必须满足的一系列要求。存储在容器中的类型必须是同类型的，必须可复制构造和可赋值的。

#### 2. C++11新增容器要求

#### 3. 序列

例如`deque`、`list`等，都是序列。它要求迭代器至少是正向迭代器，保证了元素按照一定顺序排列，不会在两次迭代之间发生变化。

```C++
#include <iostream>
#include <list>
#include <algorithm>
#include <iterator>

void outint(int n) {std::cout << n << " ";}

int main()
{
    using namespace std;
    list<int> one(5, 2);
    int stuff[5] = {1, 2, 4, 8, 6};
    list<int> two;
    two.insert(two.begin(), stuff, stuff+5);
    int more[6] = {6, 4, 2, 4, 6, 5};
    list<int> three(two);
    three.insert(three.end(), more, more+6);

    cout << "List one: ";
    for_each(one.begin(), one.end(), outint);
    cout << endl << "List two: ";
    for_each(two.begin(), two.end(), outint);
    cout << endl << "List three: ";
    for_each(three.begin(), three.end(), outint);

    three.remove(2);
    cout << endl << "List three minus 2s: ";
    for_each(three.begin(), three.end(), outint);

    three.splice(three.begin(), one);
    cout << endl << "List three after splice: ";
    for_each(three.begin(), three.end(), outint);

    cout << endl << "List one: ";
    for_each(one.begin(), one.end(), outint);

    three.unique();
    cout << endl << "List three after unique: ";
    for_each(three.begin(), three.end(), outint);
    three.sort();
    three.unique();
    cout << endl << "List three after sort & unique: ";
    for_each(three.begin(), three.end(), outint);
    two.sort();
    three.merge(two);
    cout << endl << "Sorted two merged into three: ";
    for_each(three.begin(), three.end(), outint);
    cout << endl;

    return 0;
}

/* 输出示例
List one: 2 2 2 2 2 
List two: 1 2 4 8 6 
List three: 1 2 4 8 6 6 4 2 4 6 5 
List three minus 2s: 1 4 8 6 6 4 4 6 5 
List three after splice: 2 2 2 2 2 1 4 8 6 6 4 4 6 5 
List one: 
List three after unique: 2 1 4 8 6 4 6 5 
List three after sort & unique: 1 2 4 5 6 8 
Sorted two merged into three: 1 1 2 2 4 4 5 6 6 8 8
*/
```

`insert`和`splice`区别在于，`insert`插入的是副本，而`splice`插入的是原始区间，所以序列`one`变为空。方法`unique`只能将相邻的两个相同的元素压缩为一个，所以序列`three`经过`unique`方法后还是有两个不相邻的6。需要注意这一点和普通意义上的去重的不同。

### 16.4.6 关联容器

关联容器将值与键联系在一起，可以通过键来查找值，类似于哈希表、Python中的字典等。STL中提供了4中关联容器：`set`、`multiset`、`map`和`multimap`。

#### 1. `set`示例

`set`中键是唯一的，且可以排序。

```C++
#include <iostream>
#include <string>
#include <set>
#include <algorithm>
#include <iterator>

int main()
{
    using namespace std;
    const int N = 6;
    string s1[N] = {"buffoon", "thinkers", "for", "heavy", "can", "for"};
    string s2[N] = {"metal", "any", "food", "elegant", "deliver", "for"};

    set<string> A(s1, s1+N);
    set<string> B(s2, s2+N);

    ostream_iterator<string, char> out(cout, " ");
    cout << "Set A: ";
    copy(A.begin(), A.end(), out);
    cout << endl;
    cout << "Set B: ";
    copy(B.begin(), B.end(), out);
    cout << endl;
    cout << "Union of A and B:\n";
    set_union(A.begin(), A.end(), B.begin(), B.end(), out);
    cout << endl;

    cout << "Intersection of A and B:\n";
    set_intersection(A.begin(), A.end(), B.begin(), B.end(), out);
    cout << endl;

    cout << "Difference of A and B:\n";
    set_difference(A.begin(), A.end(), B.begin(), B.end(), out);
    cout << endl;

    set<string> C;
    cout << "Set C:\n";
    set_union(A.begin(), A.end(), B.begin(), B.end(), insert_iterator<set<string>> (C, C.begin()));
    copy(C.begin(), C.end(), out);
    cout << endl;

    string s3("grungy");
    C.insert(s3);
    cout << "Set C after insertion:\n";
    copy(C.begin(), C.end(), out);
    cout << endl;

    cout << "Showing a range:\n";
    copy(C.lower_bound("ghost"), C.upper_bound("spook"), out);
    cout << endl;

    return 0;
}

/* 输出示例
Set A: buffoon can for heavy thinkers 
Set B: any deliver elegant food for metal 
Union of A and B:
any buffoon can deliver elegant food for heavy metal thinkers 
Intersection of A and B:
for 
Difference of A and B:
buffoon can heavy thinkers 
Set C:
any buffoon can deliver elegant food for heavy metal thinkers 
Set C after insertion:
any buffoon can deliver elegant food for grungy heavy metal thinkers 
Showing a range:
grungy heavy metal 
*/
```

#### 2. `multimap`示例

`multimap`键和值的类型不同，且一个键可能关联多个值。

```C++
#include <iostream>
#include <string>
#include <map>
#include <algorithm>
#include <iterator>

typedef int KeyType;
typedef std::pair<const KeyType, std::string> Pair;
typedef std::multimap<KeyType, std::string> MapCode;

int main()
{
    using namespace std;
    MapCode codes;

    codes.insert(Pair(415, "San Francisco"));
    codes.insert(Pair(510, "Oakland"));
    codes.insert(Pair(718, "Brooklyn"));
    codes.insert(Pair(718, "Staten Island"));
    codes.insert(Pair(415, "San Rafael"));
    codes.insert(Pair(510, "Berkeley"));

    cout << "Number of cities with area code 415: "
         << codes.count(415) << endl;
    cout << "Number of cities with area code 718: "
         << codes.count(718) << endl;
    cout << "Number of cities with area code 510: "
         << codes.count(510) << endl;
    cout << "Area Code\t\tCity\n";
    MapCode::iterator it;
    for (it = codes.begin(); it != codes.end(); ++it)
        cout << "\t" << (*it).first << "\t\t\t"
             << (*it).second << endl;
    pair<MapCode::iterator, MapCode::iterator> range = codes.equal_range(718);
    cout << "Cities with area code 718:\n";
    for (it = range.first; it != range.second; ++it)
        cout << (*it).second << endl;

    return 0;
}

/* 输出示例
Number of cities with area code 415: 2
Number of cities with area code 718: 2
Number of cities with area code 510: 2
Area Code		City
	415			San Francisco
	415			San Rafael
	510			Oakland
	510			Berkeley
	718			Brooklyn
	718			Staten Island
Cities with area code 718:
Brooklyn
Staten Island
*/
```

### 16.4.7 无序关联容器（C++11）

关联容器底层数据结构是树，无序关联容器底层数据结构是哈希表。

## 16.5 函数对象

### 16.5.1 函数符概念

- 生成器是不用参数就可以调用的函数符
- 一元函数是一个参数可以调用的函数符
- 二元函数是两个参数可以调用的函数符

### 16.5.2 预定义的函数符

加减乘除，关系运算等。

### 16.5.3 自适应函数符和函数适配器

没理解什么意思。但是代码能看懂。就是将二元函数转换成了一元函数，STL中的`bind1st`可以实现这种转换。

## 16.6 算法

对于STL中的算法函数，有两个主要的通用部分，首先它们都是用模板来提供泛型；其次，它们都使用迭代器来提供访问容器中的数据的通用表示。

### 16.6.1 算法组

STL将算法库分为4组：

- 非修改式序列操作，`find()`、`for_each`
- 修改式序列操作，`transform`、`random_shuffle`
- 排序和相关操作，`sort()`
- 通用数字运算

### 16.6.2 算法的通用特征

对算法分类的方式之一是根据结果放置的位置，有些算法就地完成工作，有些则创建拷贝，STL约定创建拷贝的算法以`_copy`结尾。

### 16.6.3 STL和string类

string类虽然不是STL的组成部分，但是可以使用STL接口，例如`begin()`、`rbegin()`等。

```C++
#include <iostream>
#include <string>
#include <algorithm>

int main()
{
    using namespace std;
    string letters;
    cout << "Enter the letter grouping (quit to quit): ";
    while (cin >> letters && letters != "quit") {
        cout << "Permutations of " << letters << endl;
        sort(letters.begin(), letters.end());
        cout << letters << endl;
        while (next_permutation(letters.begin(), letters.end()))
            cout << letters << endl;
        cout << "Enter next sequence (quit to quit): ";
    }
    cout << "Done.\n";

    return 0;
}

/* 输出示例
Enter the letter grouping (quit to quit): awl
Permutations of awl
alw
awl
law
lwa
wal
wla
Enter next sequence (quit to quit): all
Permutations of all
all
lal
lla
Enter next sequence (quit to quit): quit
Done.
*/
```

### 16.6.4 函数和容器方法

通常来说应该使用容器方法，因为它包含了自动的内存管理，可以对容器长度和大小进行自动缩放。但是函数更加通用。

### 16.6.5 使用STL

```C++
#include <iostream>
#include <string>
#include <vector>
#include <set>
#include <map>
#include <iterator>
#include <cctype>
#include <algorithm>
using namespace std;

char toLower(char ch) { return tolower(ch); }
string & ToLower(string & st);
void display(const string & s);

int main()
{
    vector<string> words;
    cout << "Enter words (enter quit to quit):\n";
    string input;
    while (cin >> input && input != "quit")
        words.push_back(input);			// 将词输入到vector中
    cout << "You entered the following words:\n";
    for_each(words.begin(), words.end(), display);
    cout << endl;

    set<string> wordset;		// 使用set进行排序和去重
    transform(words.begin(), words.end(),
            insert_iterator<set<string>> (wordset, wordset.begin()), ToLower);
    cout << "\nAlphabetic list of words:\n";
    for_each(wordset.begin(), wordset.end(), display);
    cout << endl;

    map<string, int> wordmap;	// 创建map,键为string,值为int
    set<string>::iterator si;
    for (si = wordset.begin(); si != wordset.end(); si++)
        wordmap[*si] = count(words.begin(), words.end(), *si);
    cout << "\nWord frequency:\n";
    for (si = wordset.begin(); si != wordset.end(); si++)
        cout << *si << ": " << wordmap[*si] << endl;

    return 0;
}

string & ToLower(string & s) {
    transform(s.begin(), s.end(), s.begin(), toLower);
    return s;
}

void display(const string & s) {
    cout << s << " ";
}
```

## 16.7 其他库

### 16.7.1 `vector`、`valarray`和`array`

`vector`是一个容器类和算法系统的一部分，它支持面向容器的操作。`valarray`是面向数值计算的，它不是STL的一部分，没有内置的`push_back()`和`insert()`方法，但是为很多数值计算提供了方便的接口。`array`是为替代内置数组而设计的，它通过更好更安全的接口让数组更紧凑，效率更高。

`valarray`类重载了一些运算符，可以很方便的完成数组的计算，类似于Python中的Numpy。

### 16.7.2 模板`initializer_list`

可以使用初始化列表语法将STL容器初始化。

### 16.7.3 使用`initializer_list`

```C++
#include <iostream>
#include <initializer_list>
using namespace std;

double sum(initializer_list<double> il);
double average(const initializer_list<double> & ril);

int main()
{
    cout << "List 1: sum = " << sum({2, 3, 4})
         << ", ave = " << average({2, 3, 4}) << "\n";
    initializer_list<double> d1 = {1.1, 2.2, 3.3, 4.4, 5.5};
    cout << "List 2: sum = " << sum(d1)
         << ", ave = " << average(d1) << "\n";
    d1 = {16.0, 25.0, 36.0, 40.0, 64.0};
    cout << "List 3: sum = " << sum(d1)
         << ", ave = " << average(d1) << "\n";

    return 0;
}

double sum(initializer_list<double> il) {
    double tot = 0;
    for (auto p = il.begin(); p != il.end(); p++)
        tot += *p;
    return tot;
}

double average(const initializer_list<double> & ril) {
    double tot = 0;
    int n = ril.size();
    double ave = 0.0;
    if (n > 0) {
        for (auto p = ril.begin(); p != ril.end(); p++)
            tot += *p;
        ave = tot / n;
    }
    return ave;
}
```

