[TOC]

# Chapter 17. 输入、输出和文件

- C++角度的输入和输出
- iostream类系列
- 重定向
- ostream类方法
- 格式化输出
- istream类方法
- 流状态
- 文件I/O
- 使用ifstream类从文件输入
- 使用ofstream类输出到文件
- 使用fstream类进行文件输入和输出
- 命令行处理
- 二进制文件
- 随机文件访问
- 内核格式化

## 17.1 C++输入和输出概述

输入输出头文件`iostream`和`fstream`。

### 17.1.1 流和缓冲区

C++把输入和输出看做字节流，程序只是检查字节流，不需要知道字节来自何方去往何处。管理输入流：

- 将流与输入去向的程序关联起来
- 将流与文件连接起来

C++使用缓冲区来更高效地处理输入和输出。

### 17.1.2 流、缓冲区和`iostream`文件

管理缓冲区的实现主要在`iostream`头文件中：

- `streambuf`类为缓冲区提供了内存，并提供了访问、刷新和管理缓冲区内存的方法；
- `ios_base`类表示流的一般特征，如是文本还是二进制，是否可读等；
- `ios`类基于`ios_base`，包含了一个指向`streambuf`对象的指针成员；
- `ostream`类是从`ios`类派生而来的，提供了输出方法；
- `istream`类也是从`ios`类派生而来的，提供了输入方法；
- `iostream`类是基于`istream`和`ostream`类的，因此继承了输入和输出方法。

### 17.1.3 重定向

## 17.2 使用`cout`进行输出

`ostream`类的重要任务之一是将数值类型转换为以文本形式表示的字符流。

### 17.2.1 重载的<<运算符

#### 1. 输出和指针

`ostream`类为一些指针类型也定义了插入运算符<<。

```C++
char name[20] = "Dudly Diddlemore";
char *pr = "Violet D'Amore";
cout << name;
cout << pr;
```

对于非字符类指针，C++将其对应于`(void *)`，并打印地址的数值表示。

```C++
int eggs = 12;
char * amount = "dozen";
cout << &eggs;				// 打印eggs的地址
cout << amount;				// 打印amount的值
cout << (void *) amount		// 打印amount的地址
```

#### 2. 拼接输出

插入运算符的所有化身的返回类型都是`ostream &`。所以：

```C++
cout << "We have " << count << " unhatched chickens.\n";
// cout << "We have "返回cout对象，使得拼接输出得以实现
```

### 17.2.2 其他`ostream`方法

除了各种版本的重载函数`operator<<()`外，`ostream`类还提供了`put()`和`write()`方法，前者用于显示字符，后者用于显示字符串。`write()`方法有两个参数，第一个是字符串地址，第二个是要显示的字符数量。

### 17.2.3 刷新输出缓冲区

一般来说，将换行符发送到缓冲区后，将刷新缓冲区，另外，C++还会在输入即将发生时刷新缓冲区。如果希望立即刷新缓冲区，可以使用`flush`：

```C++
cout << "Hello, good-looking! " << flush;
```

### 17.2.4 用`cout`进行格式化

```C++
#include <iostream>

int main()
{
    using std::cout;
    cout << "12345678901234567890\n";
    char ch = 'K';
    int t = 273;
    cout << ch << ":\n";
    cout << t << ":\n";
    cout << -t << ":\n";

    double f1 = 1.200;
    cout << f1 << ":\n";
    cout << (f1 + 1.0 / 9.0) << ":\n";

    double f2 = 1.67E2;
    cout << f2 << ":\n";
    f2 += 1.0 / 9.0;
    cout << f2 << ":\n";
    cout << (f2 * 1.0e4) << ":\n";

    double f3 = 2.3e-4;
    cout << f3 << ":\n";
    cout << f3 / 10 << ":\n";

    return 0;
}

/* 输出示例
12345678901234567890
K:
273:
-273:
1.2:
1.31111:
167:
167.111:
1.67111e+06:
0.00023:
2.3e-05:
 */
```

#### 1. 修改显示时使用的计数系统

通过`ios_base`的成员函数可以控制字段宽度和小数位数。

```C++
cout << hex;
cout << 13;		// 以16进制显示13
```

#### 2. 调整字段宽度

使用`width()`方法调整字段宽度，它只影响下一个项目，然后字段宽度会恢复为默认值。

```C++
cout << '#';
cout.width(12);
cout << 12 << "#" << 24 << "#\n";

// 输出
#            12#24#
```

另外`width()`不会截断数据，如果字段宽度设置不够，那么C++会默认显示所有数据。

#### 3. 填充字符

默认情况下，`cout`使用空格填充字段中未使用的部分，可以用`fill()`成员函数来改变填充字符。

```C++
#include <iostream>

int main()
{
    using std::cout;
    cout.fill('*');
    const char * staff[2] = { "Waldo Whipsnade", "Wilmarie Wooper"};
    long bonus[2] = {900, 1350};

    for (int i = 0; i < 2; i++) {
        cout << staff[i] << ": $";
        cout.width(7);
        cout << bonus[i] << "\n";
    }

    return 0;
}


/* 输出示例
 * Waldo Whipsnade: $****900
 * Wilmarie Wooper: $***1350
 */
```

新填充的字符会一直有效，直到修改它为止。

#### 4. 设置浮点数的显示精度

C++的默认精度为6为，可以使用`precision()`成员函数修改显示精度，而且显示精度设置一直有效，直到修改它为止。

#### 5. 打印末尾的0和小数点

对于有些输出，例如`20.40`会比`20.4`美观，`ostream`类提供了一个`setf()`函数用来控制多种格式化特性。

#### 6. 再谈`setf`

`setf()`有两个原型，第一个为`fmtflags setf(fmtflags)`。`fmtflags`用于存储格式标记，该方法返回一个`fmtflags`值，可以将现在的格式信息进行存储，以便后来进行恢复。

| 常量                  | 含义                                  |
| --------------------- | ------------------------------------- |
| `ios_base::boolalpha` | 输入和输出bool值，可以为true或false   |
| `ios_base::showbase`  | 对于输出，使用C++基数前缀（0， 0x）   |
| `ios_base::showpoint` | 显示末尾的小数点                      |
| `ios_base::uppercase` | 对于16进制输出，使用大写字母，E表示法 |
| `ios_base::showpos`   | 在正数前面加上+                       |

第二个原型接受两个参数，并返回以前的设置：

```C++
fmtflags setf(fmtflags, fmtflags);
```

第一个参数和之前一样，包含了需设置的`fmtflags`值，第二个参数指出需要清除第一个参数中的哪些位。例如将第3位设置为1表示以10为基数，第4位设置为1表示以8为基数，第5位设置为1表示以16为基数，假设输出以10为基数，那么要改成16为基数的话，不仅需要将第5位设置为1，还要将第3位设置为0，这就叫清除位。

```C++
#include <iostream>
#include <cmath>

int main()
{
    using namespace std;
    // 使用左对齐，显示符号位，显示末尾小数点
    cout.setf(ios_base::left, ios_base::adjustfield);
    cout.setf(ios_base::showpos);
    cout.setf(ios_base::showpoint);
    cout.precision(3);
    // 使用科学计数法，然后保存旧的设置
    ios_base::fmtflags old = cout.setf(ios_base::scientific, ios_base::floatfield);
    cout << "Left Justification:\n";
    long n;
    for (n = 1; n <= 41; n += 10) {
        cout.width(4);
        cout << n << "|";
        cout.width(12);
        cout << sqrt(double(n)) << "|\n";
    }
    // 设置为符号位左对齐，值右对齐
    cout.setf(ios_base::internal, ios_base::adjustfield);
    // 恢复默认的浮点数显示格式
    cout.setf(old, ios_base::floatfield);

    cout << "Internal Justification:\n";
    for (n = 1; n <= 41; n += 10) {
        cout.width(4);
        cout << n << "|";
        cout.width(12);
        cout << sqrt(double(n)) << "|\n";
    }
	// 使用右对齐，浮点数格式显示
    cout.setf(ios_base::right, ios_base::adjustfield);
    cout.setf(ios_base::fixed, ios_base::floatfield);
    cout << "Right Justification:\n";
    for (n = 1; n <= 41; n += 10) {
        cout.width(4);
        cout << n << "|";
        cout.width(12);
        cout << sqrt(double(n)) << "|\n";
    }

    return 0;
}

/* 输出示例
Left Justification:
+1  |+1.000e+00  |
+11 |+3.317e+00  |
+21 |+4.583e+00  |
+31 |+5.568e+00  |
+41 |+6.403e+00  |
Internal Justification:
+  1|+       1.00|
+ 11|+       3.32|
+ 21|+       4.58|
+ 31|+       5.57|
+ 41|+       6.40|
Right Justification:
  +1|      +1.000|
 +11|      +3.317|
 +21|      +4.583|
 +31|      +5.568|
 +41|      +6.403|
 */
```

#### 7. 标准控制符

使用`setf()`并不是最为友好的方法，可以使用控制符来实现格式化：

```C++
cout << left << fixed;		// 使用左对齐和定点选项
```

#### 8. 头文件`iomanip`

```C++
#include <iostream>
#include <iomanip>
#include <cmath>

int main()
{
    using namespace std;
    cout << fixed << right;

    cout << setw(6) << "N" << setw(14) << "square root"
         << setw(15) << "fourth root\n";
    double root;
    for (int n = 10; n <= 100; n += 10) {
        root = sqrt(double(n));
        cout << setw(6) << setfill('.') << n << setfill(' ')
             << setw(12) << setprecision(3) << root
             << setw(14) << setprecision(4) << sqrt(root)
             << endl;
    }

    return 0;
}

/* 输出示例
     N   square root   fourth root
....10       3.162        1.7783
....20       4.472        2.1147
....30       5.477        2.3403
....40       6.325        2.5149
....50       7.071        2.6591
....60       7.746        2.7832
....70       8.367        2.8925
....80       8.944        2.9907
....90       9.487        3.0801
...100      10.000        3.1623
 */
```

## 17.3 使用`cin`进行输入

`cin`可以配合`hex`、`oct`和`dec`控制符与`cin`一起使用，来将整数输入解释为对应的基数。

### 17.3.1 `cin>>`如何检查输入

