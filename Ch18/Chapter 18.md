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

为了避免在函数调用和复制的过程中需要大量的复制拷贝操作，可以只修改记录，这就是移动语义。

### 18.2.2 一个移动示例

```C++

```

