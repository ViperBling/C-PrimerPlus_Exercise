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

单字符模式下，抽取运算符>>将读取该字符，并把它放到指定位置，其他模式下，抽取运算符读取从非空白字符开始，到与目标类型不匹配的第一个字符之间的全部内容。

### 17.3.2 流状态

`cin`或`cout`对象包含一个描述流状态（`stream state`）的数据成员，由3个`ios_base`元素组成：`eofbit`、`badbit`和`failbit`，每个都是1位，可以是1或者0。到达文件末尾时，设置`eofbit`；当`cin`操作未能读取预期字符时，或者I/O失败时将设置`failbit`；在一些无法诊断的失败破坏流时，将设置`badbit`。

#### 1. 设置状态

改变流状态的方法：`clear()`和`setstate()`。`clear()`方法将状态设置为它的参数，其余的全部清除。而`setstate()`方法仅影响它的参数，对其他的位不作处理。

#### 2. I/O和异常

可以使用`exceptions()`方法来处理异常。

#### 3. 流状态的影响

如果输入流时引发了异常或修改了状态位，那么流将对后面的输入或输出关闭，直到位被清除。可以调用`cin.clear()`方法来重置流状态。然后丢弃行中剩余的部分：

```C++
cin.clear();
while (cin.get() != '\n')
    continue;
```

### 17.3.3 其他`istream`类方法

- `get(char &)`和`get(void)`提供不跳过空白的单字符输入
- `get(char *, int, char)`和`getline(char *, int, char)`默认情况下读取一整行。

#### 1. 单字符输入

使用`char`参数或没有参数的情况下，`get()`方法读取下一个输入字符，即使该字符是空格、制表符或换行符。

- `get(char & ch)`版本返回一个指向用于调用它的`istream`对象引用，可以拼接读取；

- `get(void)`版本返回值类型为`int`，不可以拼接，但是可以在抽取序列的最后使用：

  ```C++
  char c1, c2, c3;
  cin.get().get() >> c3;		// 非法
  cin.get(c1).get();			// 合法
  ```

#### 2. 采用那种单字符输入形式

如果希望跳过空白，那么使用抽取运算符`>>`比较方便；

如果希望程序检查每个字符，应该使用`get()`方法，而`get(char & ch)`版本的接口更好；

如果希望方便地把C程序转换为C++程序，那么`get(void)`版本将是不错的选择。

#### 3. 字符串输入：`getline()`、`get()`和`ignore()`

```C++
istream & get(char *, int, char);			// 最后一个参数为分界符
istream & get(char *, int);					// 该版本默认使用换行作为分界符
istream & getline(char *, int , char);
istream & getline(char *, int);
```

`getline()`和`get()`的主要区别是，`getline`方法抽取并丢弃输入流中的换行符（分界符），`get`方法则将换行符（分界符）保存在输入流中。

`ignore()`函数接受两个参数，第一个是读取的字符数，第二个是分界符：

```C++
cin.ignore(255, '\n');		// 读取并丢弃接下来255个字符，或直到到达第一个换行符
```

#### 4. 意外字符串输入

| 方法                   | 行为                                                         |
| ---------------------- | ------------------------------------------------------------ |
| `getline(char *, int)` | 如果没有读取任何字符（换行被视为读取一个字符），则设置fallbit<br />如果读取了最大数目的字符，且行中还有其他字符，则设置fallbit |
| `get(char *, int)`     | 如果没有读取任何字符，则设置fallbit                          |

### 17.3.4 其他`istream`方法

除了前面讨论的以外，还有`read()`、`peek()`、`gcount()`和`putback()`。

```C++
cin.read(gross, 144);				// 从流中读取144个字节，放到gross数组中，不包括空字符
cin.peek();							// 返回输入中下一个字符，不抽取流中字符
```

`gcount()`方法返回非格式化读取的字符数，这意味着字符**不是**由抽取运算符`>>`读取的。

`putback()`方法将一个字符插入到输入字符串中，被插入的字符将是下一条输入语句读取的第一个字符。

## 17.4 文件输入和输出

### 17.4.1 简单的文件I/O

要让程序写入文件：

1. 创建一个`ofstream`对象来管理输出流；
2. 将该对象与特定的文件关联起来；
3. 以使用`cout`的方式使用对象。

### 17.4.2 流状态检查和`is_open()`

`is_open()`方法可以用来检查文件是否被打开，而且同时能够检查到是否以合适的模式打开了文件。

### 17.4.3 打开多个文件

```C++
ifstream fin("fat.txt");
...
fin.close();
fin.clear();
fin.open("rat.txt");
...
fin.close();
```

### 17.4.4 命令行处理技术

```C++
int main(int argc, char * argv[])
// argc为命令行参数的个数，包括命令名本身
// argv为一个指针，指向每个参数字符串
```

### 17.4.5 文件模式

```C++
ifstream fin("banjo", model);			// model为文件模式，读、写、追加等
```

| 常量               | 含义                     |
| ------------------ | ------------------------ |
| `ios_base::in`     | 打开文件，以便读取       |
| `ios_base::out`    | 打开文件，以便写入       |
| `ios_base::ate`    | 打开文件，并移到文件结尾 |
| `ios_base::app`    | 追加到文件尾             |
| `ios_base::trunc`  | 如果文件存在，则截短文件 |
| `ios_base::binary` | 二进制文件               |

#### 1. 追加文件

使用`ios_base::app`模式打开。

#### 2. 二进制文件

二进制文件中的字符表示和文本文件一样，但是数字表示差别很大。二进制文件数字存储的是内部的值，没有舍入误差。

### 17.4.6 随机存取

随机存取指的是直接移动到文件任何位置。可以使用`seekp()`和`seekg()`方法，前者将输出指针移到指定的文件位置，后者将输入指针移到指定的文件位置。

```C++
fin.seekg(30, ios_base::beg);		// 开始位置后面的30个字节
fin.seekg(-1, ios_base::cur);		// 当前位置的前一个字节
fin.seekg(0, ios_base::end);		// 文件尾
```

## 17.5 内核格式化

读取string对象中的格式化信息或将格式化信息写入string对象中被称为内核格式化。主要定义在头文件`sstream`中。