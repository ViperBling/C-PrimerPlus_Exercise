[TOC]

# Chapter 18. 探讨C++新标准

- 移动语义和右值引用
- Lambda表达式
- 包装器模板function
- 可变参数模板

## 18.1 复习前面介绍过的C++11功能

### 18.1.1 新类型

long long，usigned long long；

char16_t，char32_t

### 18.1.2 统一的初始化

```C++
int x = {5};
double y{2.75};
```

#### 1. 缩窄

初始化列表可以防止数据缩窄，即禁止将数值赋给无法存储它的变量。

```C++
char c1 = 1.57e27;		// 未定义的行为，但是可以通过编译
char c1 {1.57e27};		// 无法通过编译
```

#### 2. `std::initializer_list`

C++11提供了模板类`std::initializer_list`，可将其作为构造函数的参数。

### 18.1.3 声明

#### 1. `auto`

`auto`可以用于自动类型推断。

#### 2. `decltype`

`decltype`将变量声明为表达式指定的类型：

```C++
double x;
int n;
decltype(x * n) q;		// 将q声明为double
```

#### 3. 返回类型后置

```C++
double f1(double, int);			// 传统声明
auto f2(double, int) -> double; // 新特性
```

这样就允许使用`decltype`来指定模板函数的返回类型：

```C++
template <typename T, typename U>
auto eff(T t, U u) -> decltype(T * U) {}
```

#### 4. 模板别名：`using`

```C++
typedef std::vector<std::string>::iterator itType;		// 传统做法
using itType = std::vector<std::string>::iterator;		// 新特性
template<typename T>
using arr12 = std::array<T, 12>; 				// 新特性可以这样做，typedef不行
```

#### 5. `nullptr`

使用`nullptr`代替0.

### 18.1.4 智能指针

智能指针用于自动化的内存释放。

### 18.1.5 异常规范方面的修改

C++11摒弃了异常规范，为了指出函数不会引发异常，新增关键字`noexcept`。

### 18.1.6 作用域内枚举

为了避免枚举成员名之间的冲突，C++11新增了作用域内枚举：

```C++
enum Old1 {yes, no, maybe};					// 传统形式
enum class New1 {never, sometimes, often, always};	// 新形式
enum struct New2 {never, lever, server};
```

### 18.1.7 对类的修改

#### 1. 显示转换运算符

自动类型转换有时会导致一些问题，为此，C++引入`explicit`关键字来禁止隐式的自动转换。

#### 2. 类内成员初始化

现在可以在类内对成员进行初始化了。

```C++
class Session {
    int mem1 = 10;
    double mem2 {1966.54};
    short mem3;
public:
    Session() {}
    Session(short s) : mem3(s) {}
    Session(int n, double d, short s) : mem1(n), mem2(d), mem3(s) {}
};
```

### 18.1.8 模板和STL方面的修改

#### 1. 基于范围的for循环

```C++
double prices[5] = {4.99, 10.99, 6.87, 7.99, 8.49};
for (auto x : prices)
    std::cout << x << std::endl;
```

如果要修改数组或容器的值，则注意要使用引用。

#### 2. 新的STL容器

C++11新增了容器，具体参见第16章。还新增了模板`array`

#### 3. 新的STL方法

新增了`cbegin()`和`cend()`。这些方法将元素视为`const`。

#### 4. `valarray`的升级

现在，基于范围的STL算法也可以用于`valarray`了。

#### 5. 摒弃`export`

#### 6. 尖括号

为了避免与运算符>>混淆，之前要求要用空格将嵌套模板时的尖括号分开，现在不需要了。

### 18.1.9 右值引用

```C++
#include <iostream>

inline double f(double tf) { return 5.0 * (tf - 32.0) / 9.0; }

int main()
{
    using namespace std;
    double tc = 21.5;
    double && rd1 = 7.07;
    double && rd2 = 1.8 * tc + 32.0;
    double && rd3 = f(rd2);
    cout << " tc value and address: " << tc << ", " << &tc << endl;
    cout << "rd1 value and address: " << rd1 << ", " << &rd1 << endl;
    cout << "rd2 value and address: " << rd2 << ", " << &rd2 << endl;
    cout << "rd3 value and address: " << rd3 << ", " << &rd3 << endl;
    cin.get();

    return 0;
}

/* 输出示例
 tc value and address: 21.5, 0x7fff2ccdd490
rd1 value and address: 7.07, 0x7fff2ccdd498
rd2 value and address: 70.7, 0x7fff2ccdd4a0
rd3 value and address: 21.5, 0x7fff2ccdd4a8
*/
```

## 18.2 移动语义和右值引用

### 18.2.1 为何需要移动语义

为了避免在函数调用和复制的过程中需要大量的复制拷贝操作，可以只修改记录，这就是移动语义。对于类而言，可以实现两个构造函数，一个关联到左值实参，一个关联到右值实参，复制构造函数执行深度复制，移动构造函数只调整记录。

### 18.2.2 一个移动示例

```C++
#include <iostream>
using namespace std;

class Useless {
private:
    int n;
    char * pc;
    static int ct;
    void ShowObject() const;

public:
    Useless();
    explicit Useless(int k);
    Useless(int k, char ch);
    Useless(const Useless & f);
    Useless(Useless && f);
    ~Useless();
    Useless operator+(const Useless & f) const;
    void ShowData() const;
};

Useless::Useless(Useless && f) : n(f.n) {
    ++ct;
    cout << "move constructor called; number of objects: " << ct << endl;
    pc = f.pc;
    f.pc = nullptr;
    f.n = 0;
    ShowObject();
}

int main() {
    {
        Useless one(10, 'x');
        Useless two = one;
        Useless three(20, 'o');
        Useless four (one + three);		// 右值引用，调用上面的函数，因为one+three是右值

        cout << "object one: ";
        one.ShowData();
        cout << "object two: ";
        two.ShowData();
        cout << "object three: ";
        three.ShowData();
        cout << "object four: ";
        four.ShowData();
    }
}
```

**右值引用**：首先是左值和右值的区别，左值的定义表示的是可以取地址的对象，能出现在赋值语句的左边。右值表示无法获取地址的对象，常量、函数返回值、Lambda表达式等。

```C++
int i = 10;		// i是左值，10是右值
int x = x + i;	// x是左值，x+i是右值
```

传统的C++引用为左值引用，如下：

```C++
int i = 10;
int & ii = i;		// 传统引用
```

C++11中新增了右值引用，可以直接对右值进行引用，右值被存储到指定位置，右值引用指向该位置。所以，虽然右值无法获取地址，但是右值引用是可以的，该地址表示临时对象的存储位置：

```C++
int && ii = 10;		// 右值引用
```

### 18.2.3 移动构造函数解析

要使用移动语义，需要两步，第一，要让编译器知道何时使用移动语义，第二，要编写移动构造函数，使其提供所需行为。

### 18.2.4 赋值

同样，适用于构造函数的移动语义也适用于赋值运算符。

### 18.2.5 强制移动

使用`move()`方法可以方便的触发移动语义。右值引用带来的好处主要是实现移动语义。

## 18.3 新的类功能

### 18.3.1 特殊的成员函数

C++11新增了移动构造函数和移动赋值运算符。

### 18.3.2 默认的方法和禁用的方法

使用`default`关键字来指明使用编译器提供的默认版本，使用`delete`关键字，将禁用编译器使用特定的方法，例如要禁止复制对象：

```C++
class Someclass {
public:
    Someclass() = default;						// 使用默认构造函数
    Someclass(const Someclass &) = delete;		// 禁用复制构造函数
};
```

### 18.3.3 委托构造函数

类中一般需要提供多个构造函数，为了避免编写重复代码，可以使会用委托构造函数：

```C++
class Note {
    int k;
    double x;
    string st;
public:
    Note();
    Note(int);
    Note(int, double);
    Note(int, double, string);
};
Note::Note(int kk, double xx, string stt) : k(kk), x(xx), st(stt) {}
Note::Note() : Notes(0, 0.01, "Oh") {}
Note::Note(int kk) : Note(kk, 0.01, "Ah") {}
Note::Note(int kk, double xx) : Note(kk, xx, "Uh") {}
```

### 18.3.4 继承构造函数

```C++
class BS {
    int q;
    double w;
public:
    BS() : q(0), w(0) {}
    BS(int k) : q(k), w(100) {}
    BS(int k, double x) : q(k), w(x) {}
};

class DR : public BS {
    short j;
public:
    using BS::BS;				// 继承构造函数
    DR() : j(-100) {}
    DR(double x) : BS(2 * x), j(int(x)) {}
    DR(int i) : j(-2), BS(i, 0.5 * i) {}
}
```

### 18.3.5 管理虚方法：`override`和`final`

C++中的多态主要通过虚方法来实现。在C++11中，可以使用`override`说明符指出要覆盖的基类的一个虚函数。说明符`final`可以禁止派生类覆盖基类特定的虚方法。

## 18.4 Lambda函数

```C++
[&count](int x) {count += (x % 13 == 0);}
```

### 18.4.1 比较函数指针、函数符和Lambda函数

使用Lambda函数判断一个列表中的元素是否能被3整除：

```C++
count3 = count_if(numbers.begin(), numbers.end(), [](int x){return x % 3 == 0;});
```

完整示例：

```C++
#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
#include <ctime>
using namespace std;

const long Size1 = 39L;
const long Size2 = 100 * Size1;
const long Size3 = 100 * Size2;
bool f3(int x) { return x % 3 == 0; }
bool f13(int x) { return x % 13 == 0; }

int main() {
    vector<int> numbers(Size1);
    srand(time(0));
    generate(numbers.begin(), numbers.end(), rand);

    cout << "Sample size = " << Size1 << "\n";
	
    // 使用函数指针
    int count3 = count_if(numbers.begin(), numbers.end(), f3);
    cout << "Count of numbers divisible by 3: " << count3 << "\n";
    int count13 = count_if(numbers.begin(), numbers.end(), f13);
    cout << "Count of numbers divisible by 13: " << count13 << "\n\n";

    numbers.resize(Size2);
    generate(numbers.begin(), numbers.end(), rand);
    cout << "Sample size = " << Size2 << "\n";

    class f_mod {
    private:
        int dv;
    public:
        f_mod(int d = 1) : dv(d) {}
        bool operator()(int x) { return x % dv == 0; }
    };
	
    // 使用函数符
    count3 = count_if(numbers.begin(), numbers.end(), f_mod(3));
    cout << "Count of numbers divisible by 3: " << count3 << "\n";
    count13 = count_if(numbers.begin(), numbers.end(), f_mod(13));
    cout << "Count of numbers divisible by 13: " << count13 << "\n\n";

    numbers.resize(Size2);
    generate(numbers.begin(), numbers.end(), rand);
    cout << "Sample size = " << Size3 << "\n";
	
    // 使用Lambda函数
    count3 = count_if(numbers.begin(), numbers.end(), [](int x){ return x % 3 == 0; });
    cout << "Count of numbers divisible by 3: " << count3 << "\n";
    count13 = count_if(numbers.begin(), numbers.end(), [](int x){ return x % 13 == 0; });
    cout << "Count of numbers divisible by 13: " << count13 << "\n";

    return 0;
}
```

### 18.4.2 为何使用lambda

**距离**：让定义在使用的地方很方便，可以随时查看定义内容。

**简洁**：函数符比函数和lambda代码更加繁琐。可以给lambda指定名称。

**效率**：lambda可以捕获作用域内任何动态变量。

```C++
int count3 = 0;	int count13 = 0;
for_each(numbers.begin(), numbers.end(), [&](int x){count3 += x % 3 == 0; count13 += x % 13 == 0;});		// 一个表达式同时计算可被3和13整除的元素数量
```

## 18.5 包装器

`bind`、`men_fn`和`reference_wrapper`。

### 18.5.1 包装器function及模板的低效性

在正常使用模板函数时，传入模板函数的参数类型不同会导致模板函数被多次实例化。

### 18.5.2 修复问题

包装器function可以修复上述问题，使模板只实例化一次。它可以用于包装特征标相同的函数指针，函数对象或lambda表达式。

```C++
function<double(char, int)> fdci;	// 接受一个char，一个int，返回double
```

### 18.5.3 其他方式

可以使用`typedef`简化包装器function的使用：

```C++
typedef function<double<double> fdd;
cout << use_f(y, fdd(dub)) << endl;
```

也可以在模板函数里面将形参声明为包装器function：

```C++
template <typename T>
T use_f(T v, std::function<T(T)> f) {
    ...;
    return f(v);
}

cout << use_f<double>(y, dub) << endl;
```

## 18.6 可变参数模板

可变参数模板允许创建具有可变个参数的模板函数和模板类。要完成这样的工作，需要理解：

- 模板参数包（parameter pack）；
- 函数参数包
- 展开参数包
- 递归

### 18.6.1 模板和函数参数包

使用省略号表示的元运算符可以声明表示模板参数包的标识符：

```C++
template<typename... Args>
void show_list1(Args... args) {}
```

上述代码中，`Args`和任意数量类型匹配，因此可以这样调用：

```C++
show_list1('S', 80, "sweet", 4.5);
```

### 18.6.2 展开参数包

如何使函数访问参数包的内容呢？

```C++
template<typename... Args>
void show_list1(Args... args) {
	show_list1(args...);		// 将参数包展开
}
```

但是这样很明显，导致无限递归。

### 18.6.3 在可变参数模板函数中使用递归

解决方法是，将第一项展开出来进行处理，余下的参数递归处理：

```C++
template <typename T, typename... Args>
void show_list2(T value, Args... args) {}
```

但是这样还有个问题，没有递归终止条件。可以再加一个空函数来终止递归：

```C++
void show_list2() {}
template <typename T, typename... Args>
void show_list2(T value, Args... args) {}
```

## 18.7 C++11新增的其他功能

### 18.7.1 并行编程

### 18.7.2 新增的库

### 18.7.3 低级编程

低级是指抽象程度。放松了POD要求，POD是标量类型（单值类型），可逐字节赋值的东西。

另一项就是允许共用体的成员有构造函数和析构函数。

解决了内存对齐问题。

### 18.7.4 杂项

assert断言等。

## 18.8 语言变化

### 18.8.1 Boost项目

### 18.8.2 TR1

TR1（Technical Report 1），Boost占了很大一部分，包括`tuple`等。

### 18.8.3 使用Boost

