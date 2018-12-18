[TOC]

# Chapter 9. 内存模型和名称空间

## 9.1 单独编译

**程序组成**：头文件+源代码文件

**头文件中包含的内容：**

1. 函数原型
2. 使用``#define``或`const`定义的符号常量
3. 结构声明
4. 类声明
5. 内联函数
6. 模板函数

**避免多次包含头文件**：使用预编译指令``#ifndef``

## 9.2 内存持续性、作用域和链接性

C++中的数据存储类型：

1. 自动存储持续性：变量随着代码块创建，在代码块结束时自动释放。C++有两种存储持续性为自动的变量。
2. 静态存储持续性：变量在整个程序的运行过程中都存在。C++有3中存储持续性为静态的变量。
3. 线程存储持续性：如果变量是关键字```thread_local```声明的，则其声明周期和所属线程一样长。
4. 动态存储持续性：使用new运算符分配的内存将一直存在到delete运算符将其释放或程序结束为止。这种也被成为自由存储或堆。

### 9.2.1 作用域和链接

1. 作用域描述了名称在文件的多大范围可见。例如函数内部定义的变量只有函数内部可见，对其他函数是不可见的。而在文件中的函数定义之前定义的变量可在所有的函数中使用。
2. 链接性描述了名称如何在不同文件中共享。链接为外部的可以在文件之间共享，为内部的可以在一个文件的函数间共享。自动变量没有链接性，不能共享。

C++的存储方式：存储持续性、作用域、链接性。

### 9.2.2 自动存储持续性

在函数中声明的函数参数和变量的存储持续性为自动，作用域为局部，没有链接性。这种变量的生命周期依赖于代码块（花括号），代码块内声明的变量到代码块结束时销毁。如果在函数内部的代码块中定义了同名的变量，那么新的定义将覆盖代码块之前的定义直到当前代码块结束。

**自动变量和栈**：函数被调用时，自动变量被压入栈顶，函数调用结束后恢复栈顶指针，释放自动变量的内存。

### 9.2.3 静态存储变量

C++为静态存储持续性提供了3种链接性：外部链接性（文件间），内部链接性（文件内部），无链接性（当前函数和代码块）。

### 9.2.4 静态持续性、外部链接性

链接性为外部的变量存储持续性为静态，作用域为整个文件。

**单定义规则**：变量只能有一次定义。C++提供两种变量声明，一种是定义（分配存储），一种是引用声明（不分配存储）

```C++
double up; 			     // 外部变量定义，默认初始为0
extern int blem;         // blem在其他地方已经定义，这里是引用声明
extern char gr = 'z'     // 定义，因为被初始化
```

`extern`关键字用于声明在其他文件中已经定义的变量。

### 9.2.5 静态持续性、内部链接性

将`static`限定符用于作用域为整个文件的变量时，链接性为内部。多文件程序中，普通的静态变量可以被其他文件使用`extern`关键字引用，具有外部链接性，但是加上了`static`限定符的变量的作用域仅为当前文件。

### 9.2.6 静态持续性、无链接性

将`static`限定符用于在代码块中定义变量，这样导致局部变量的存储持续性为静态的，但是虽然该变量只能在代码块内使用，但是在代码块不处于活动状态的时候仍然存在。因此在两次函数调用期间，静态局部变量的值保持不变。

```C++
// 统计单次输入字符个数和字符总数
#include <iostream>

const int ArSize = 10;

void strcount(const char * str);

int main()
{
    using namespace std;
    char input[ArSize];
    char next;

    cout << "Enter a line:\n";
    cin.get(input, ArSize);
    // 利用cin的返回值判断是否为空行
    while (cin){
        cin.get(next);
        // 过滤回车
        while (next != '\n')
            cin.get(next);
        strcount(input);
        cout << "Enter next line (empty line to quit):\n";
        cin.get(input, ArSize);
    }
    cout << "Bye!\n";
}

void strcount(const char * str)
{
    using namespace std;
    // 使用静态局部变量保存字符总数
    static int total = 0;
    int count = 0;

    cout << "\"" << str << "\" contains ";
    while (*str++)
        count++;
    total += count;
    cout << count << " characters\n";
    cout << total << " characters total\n";
}
```

上述代码中，使用`static`限定符作用于变量`total`，在函数调用结束后，变量仍然存在，所以可以用来累加字符总数。

### 9.2.7 说明符和限定符

存储说明符：auto，register，static，extern，thread_local，mutable

1. cv-限定符：const，volatile。volatile关键字表明即使程序没有修改变量，其值也有可能发生变化。

2. mutable：用它来指出，即使结构或类变量为const，某个成员也可以被修改

   ```C++
   struct data{
       char name[30];
       mutable int accesses;
       ...
   };
   const data veep = {"Claybourne Clodde", 0, ...};
   strcpy(veep.name, "Joye Joux");     // 非法操作，限定为const
   veep.accesses++;                    // 合法操作，加入了mutable
   ```

3. 注意，在C++中，全局const限定符的链接性为内部，也就是说和static类似。

### 9.2.8 函数和链接性

C++中所有函数的存储持续性都是静态的。默认情况下，函数的链接性为外部的，可以在文件间共享。使用`static`限定符可以将函数限制在文件内部使用，这样不必担心和其他文件的函数名冲突。

### 9.2.9 语言链接性

链接程序要求每个函数都有不同的函数名，在C++编译器编译的时候会执行名称矫正，为重载函数生成不同的符号名称，这被称为C++语言链接。如果要使用C库中的函数，可以在原型中指定查找位置为C库：

```C++
extern "C" void spiff(int);		// 使用C库中的spiff函数
extern void spiff(int);			// 使用C++库中的spiff函数
extern "C++" void spiff(int);	// 使用C++库中的spiff函数
```

### 9.2.10 存储方案和动态分配

使用new运算符分配的内存成为动态内存，前面说的内存分配方案不适用于这种动态内存。动态内存的分配和释放取决于new和delete的使用时间。通常编译器使用三块独立的内存：静态变量、自动变量、动态存储。

**定位new运算符**：这是new运算符的一个变种，可以让程序员指定要使用的内存位置。

```C++
#include <new>
struct chaff{
    char dross[20];
    int slag;
};
char buffer1[50];
char buffer2[500];
int main(){
    chaff *p1, *p2;
    int *p3, *p4;
    // 默认在堆中分配新的chaff内存结构和int内存
    p1 = new chaff;
    p3 = new int[20];
    // 通过new运算符指定p2指向的位置为字符数组buffer1.
    p2 = new (buffer1) chaff;
    p4 = new (buffer2) int[20];
}
```

## 9.3 名称空间

为了避免越来越多的名称发生冲突，控制各个名称的作用域，C++提供了名称空间工具。

### 9.3.1 传统的C++名称空间

声明区域：全局变量的声明区域为整个文件，局部变量为其所在的代码块

潜在作用域：从声明点开始到声明区域的结尾。也就是从定义开始到作用域的结尾。

### 9.3.2 新的名称空间

新的特性中允许创建一个声明区域来命名名称空间：

```C++
namespace Jack{
    double pail;
    void fetch();
    int pal;
    struct Well { ... };
}
namespace Jill{
    double bucket (double n) { ... }
    double fetch;
    int pal;
    struct Hill { ... };
}
```

如上面代码所示，两个名称空间中的变量是互不冲突的，即使重名也可以同时使用。

名称空间可以是全局的，也可以位于另外一个名称空间中，但不能位于代码块中。可以使用作用域解析运算符来访问名称：

```C++
Jack::pail = 12.34;
Jill::Hill mole;
```

`using`声明和`using`编译指令：`using`声明可以指定名称空间中的名称，在后面的代码中就可以直接使用该名称：

```C++
using Jack::pail;
pail = 3.1;
```

`using`编译指令可以使用名称空间中所有的名称：

```C++
using namespace Jill;
fetch = 3.1;
Hill mole;
```

