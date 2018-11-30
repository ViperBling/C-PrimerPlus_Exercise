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

这种函数的使用方式，类似Python中的lambda函数，但是更为底层。

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

