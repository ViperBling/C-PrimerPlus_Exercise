[TOC]

# Chapter 8. C++新特性

## 8.1 内联函数

在内联函数中，编译器使用函数代码替换相应的函数调用。在执行过程中，不需要调到被调函数的地址然后在跳回主调函数，而是直接在主调函数内部执行内联函数，可以节省程序运行时间：

```C++
#include <iostream>
inline double square(double x) { return x * x; }

int main()
{
    using namespace std;
    double a, b;
    double c;
    
    a = square(5.0);
    b = square(4.5 + 7.5);   // 可以传递表达式
    cout << "a = " << a << ", b = " << b << endl;
    cout << "c = " << c;
    cout << ", c squared = " << square(c++) << "\n";
    cout << "Now c = " << c << "\n";
    
    return 0;
}
```

与宏定义的区别：宏定义是通过文本替换实现的，而不是参数传递，并不是真正的函数调用。



## 8.2 引用变量

### 8.2.1 创建引用变量

引用变量是指声明一个原变量的引用，和原变量共享相同的内存地址和值，当对引用变量进行修改时，原变量也会随之改变。

使用引用变量要注意：**必须在声明引用变量时进行初始化**，不能像指针那样，先声明再赋值。而且不能通过赋值来改变引用，这样会把原变量的值也修改。总之，引用变量和原变量是捆绑在一起的。

```C++
#include <iostream>
using namespace std;

int main()
{
    int rats = 101;
    int & rodents = rats;
    cout << "rats = " << rats;
    cout << ", rodents = " << rodents << endl;
    rodents++;
    cout << "rats = " << rats;
    cout << ", rodents = " << rodents << endl;

    cout << "rats address = " << &rats;
    cout << ", rodents address = " << &rodents << endl;

    return 0;
}
```

### 8.2.2 将引用变量作为参数

按引用传递参数可以使被调函数访问主调函数中的变量，并对其进行修改，这一特性和指针相同，按值传递使用的是主调函数变量的拷贝，不会对原变量进行修改。

```C++
void swap(int & a, int & b);
```

上面演示了使用引用变量作为参数的函数原型声明。

### 8.2.3 引用的属性和特别之处

```C++
#include <iostream>
using namespace std;

double cube(double a);
double refcube(double &ra);

int main()
{
    double x = 3.0;

    cout << cube(x);
    cout << " = cube of " << x << endl;
    cout << refcube(x);
    cout << " = cube of " << x << endl;

    return 0;
}

double cube(double a)
{
    a *= a * a;
    return a;
}

double refcube(double &ra)
{
    ra *= ra * ra;
    return ra;
}
```

上述代码，输出如下：

```C++
27 = cube of 3
27 = cube of 27
```

```refcube()```修改了x的值，所以使用引用变量也要注意这种风险。加入常量引用可以解决这种问题。

```C++
double refcube(const double & ra)
```

使用上述常量引用的方式，可以避免函数执行过程中修改传递过来的参数。同时也可以使函数处理临时匿名变量类似于``x + 7.0``这种。这时函数的行为类似按值传递，不会修改参数值。

### 8.2.4 将引用用于结构

```c++
free_throws & accumulate(free_throws & target, const free_throws & source)
{
    target.attempts += source.attempts;
    target.made += source.made;
    set_pc(target);
    return target;
}
```

上面的```accumulate```函数返回的是一个```free_throws```类型的引用，然后可以把它的返回值作为引用传递个另外一个函数：```display(accumulate(team, two))```。

```C++
accumulate(dup, five) = four;
```

上述语句中，```accumulate```返回一个引用，并被赋值为```four```。

**为何要返回引用**： 如果使用原始的返回机制，计算return后的表达式，然后把结果返回，这个过程中返回值被多次复制到临时内存中，而使用引用时，直接把return返回的引用变量复制给指定变量，效率更高，尤其在较大的结构体中，这种效率的提升更加明显。

**注意事项**：应该避免使用已被释放的内存返回引用，下述代码就属于这样：

```c++
const free_throws & clone2(free_throws & ft)
{
    free_throws newguy;
    newguy = ft;
    return newguy;
}
```

这里，函数中的```newguy```变量在函数运行结束后将不存在，所以不能作为引用返回。解决方法是使用指针或者new方法来分配内存。

### 8.2.5 将引用用于类

引用在用于类使和上面一样，在被调函数内部声明的变量将在函数调用结束后销毁，所以下面的代码是错误的：

```c++
const string & version3(string & s1, const string & s2)
{
    string temp;
    temp = s2 + s1 + s2;
    return temp;
}
```

上述代码从函数头可以看到，返回的是一个```string``类型的引用，但是，由于在函数内部temp是新声明的类，在函数运行结束将不存在，因此无法作为引用被传出。

**何时使用引用**：要传递的参数为类、较大的结构时适宜使用引用。

## 8.3 默认参数

C++的默认参数和Python类似，声明方法也类似。但是C++中默认参数的声明是在函数原型中的，而不是定义中。

```C++
char * left(const char * str, int n = 1);
```

## 8.4 函数重载

函数重载的关键是函数的参数列表——函数特征标（function signature）。

**函数重载注意事项**：

 1. 没有匹配的原型并不会自动停止使用某一个函数，C++会尝试使用类型转换来强制匹配。但是如果有多个转换方式，那么编译器将会报错。

 2. 看起来不同的特征标是无法共存的，比如引用，编译器将类型引用和类型本身视为同一特征标：

    ```C++
    double cube(double x);
    double cube(double & x);
    ```

    上述代码引用时，```cube(x)```编译器无法判断使用哪个原型。

	3. 匹配函数时，不区分```const```和非```const```变量。

## 8.5 函数模板

函数模板用于让编译器根据具体类型生成函数，也被称为通用编程。

```C++
template <typename AnyType>
void swap(AnyType & a, AnyType & b)
{
    AnyType temp;
    temp = a;
    a = b;
    b = temp;
}
```

上述代码是一个交换两个元素值的函数模板。下面是具体程序示例，注意，在声明模板的时候，必须要在模板函数的原型和定义处都加上模板声明：

```C++
#include <iostream>
using namespace std;

// 第一处模板定义
template <typename T>
void Swap(T &a, T &b);

int main()
{
    int i = 10;
    int j = 20;
    cout << "i, j = " << i << ", " << j << ".\n";
    cout << "Using compiler-generated int swapper:\n";
    Swap(i, j);
    cout << "Now i, j = " << i << ", " << j << ".\n";

    double x = 24.5;
    double y = 81.7;
    cout << "x, y = " << x << ", " << y << ".\n";
    cout << "Using compiler-generated double swapper:\n";
    Swap(x, y);
    cout << "Now x, y = " << x << ", " << y << ".\n";

    return 0;
}

// 第二处模板定义
template <typename T>
void Swap(T &a, T &b)
{
    T temp;
    temp = a;
    a = b;
    b = temp;
}
```

### 8.5.1 重载的模板

模板也可以像函数那样进行重载，同样特征标也是参数列表。

```C++
template <typename T>
void Swap(T &a, T &b);

template <typename T>
void Swap(T *a, T *b, int n);
```

### 8.5.2 模板的局限性

对于上述交换两个变量值的函数来说，就无法直接应用到结构中。所以编写的模板函数很可能无法处理某些类型。其中一种解决方法就是为特定的类型提供具体化的模板定义。

### 8.5.3 显式具体化

- 对于给定函数名，可以有**非模板版本**、**模板函数**和**显式具体化模板函数**以及它们的**重载版本**。
- 显式具体化的原型和定义应以```template <>```打头，并通过名称来指定类型
- 优先级：非模板函数 > 具体化 > 常规模板

```C++
// 非模板函数
void Swap(job &, job &);

// 模板函数
template <typename T>
void Swap(T &, T &);

// job类型的显式具体化
template <> void Swap<job>(job &, job &);
```

### 8.5.4 实例化和具体化

在代码中包含函数模板本身不会生成函数定义，只是生成一个方案。当编译器使用模板定义的时候，会生成模板实例。实例化又分为隐式实例化和显式实例化。上述针对结构体job的```swap```模板函数就是显式实例化，因为它指定了要参数类型，而另外一个并没有指定，在编译器使用中才会根据代码上下文判断参数类型来进行隐式实例化。

```C++
// 显式实例化
template void Swap<int> (int, int);

// 显式具体化，下面两个声明等价
template <> void Swap<int> (int &, int &);
template <> void Swap(int &, int &);
```

注意显式实例化和显式具体化的区别。显式具体化的意思是：不要使用```Swap```模板来生成函数定义，而应该使用专门为```int```类型显示定义的函数定义。显式具体化必须有自己的函数定义，通常后面直接跟上```{}```开始函数定义，而显式实例化后面还要有单独的函数定义。

隐式实例化、显式实例化和显式具体化统称为具体化。

|         隐式实例化         |                显式实例化                |                         显式具体化                          |
| :------------------------: | :--------------------------------------: | :---------------------------------------------------------: |
|   template <typename T>    |    template void Swap<int>(int, int)     |          template <> void Swap<int>(int &, int &)           |
| 在调用时产生具体的实例类型 | 类型在定义时已经确定，直接创建对应的实例 | 这种声明指定不用模板定义，而是用后面专门为int定义的函数定义 |

```C++
template <class T>
void Swap (T &, T &);	// 函数模板

// job结构的显式具体化
template <> void Swap<job>(job &, job &);
int main(void)
{
    // 显式实例化
    template void Swap<char>(char &, char &);
    
    // short的隐式实例化
    short a, b;
    Swap(a, b);
    
    // job的显式具体化
    job n, m;
    Swap(n, m);
    
    // char的显式模板实例化
    char g, h;
    Swap(g, h);
}
```

###  8.5.5 函数版本的选择

函数重载解析 ：

- 创建候选函数列表，其中包含与被调用函数的名称相同的函数和模板函数
- 使用候选函数列表创建可行函数列表，这些都是参数数目正确的函数，为此会有一个隐式的转换序列
- 确定是否有最佳的可行参数

非模板 > 显式具体化 > 显示实例化 > 隐式实例化

提升转换 > 标准转换 > 用户自定义转换