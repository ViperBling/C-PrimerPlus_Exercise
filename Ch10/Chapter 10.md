# Chapter 10. 对象和类

OOP：

- 抽象
- 封装和数据隐藏
- 多态
- 继承
- 代码的可重用性

## 10.1 过程性编程和面向对象编程

采用OOP方法时，首先从用户的角度考虑对象——描述对象所需的数据以及描述用户与数据交互所需的操作。完成对接口的描述后，需要确定如何实现接口和存储数据。最后，使用新的设计方案创建出程序。

## 10.2 抽象和类

### 10.2.1 类型

指定类型：

- 决定数据对象需要的内存数量
- 决定如何解释内存中的bit
- 决定可使用数据对象执行的操作或者方法

简而言之，类型就是数据在内存中的表示以及定义在类型上的操作的集合。

### 10.2.2 C++中的类

类：

- 类声明：以数据成员的方式描述数据部分，以成员函数（方法）的方式描述公有接口
- 类方法定义：描述如何实现成员函数（如何实现接口）

通常，C++将接口定义在头文件中，将实现的方法放在源代码中。

1. 访问控制

   使用类的程序可以直接访问公有成员函数，但是只能通过公有成员函数来访问对象的私有成员。

2. 控制对成员的访问

   数据项通常放在私有部分，成员函数放在公有部分，通常隐藏关键字`private`。

### 10.2.3 实现类成员函数

- 定义成员函数时，可以使用作用域解析运算符(::)来标识函数所属的类
- 类方法可以访问private组件
内联方法：所有定义在类声明中的函数都将自动成为内联函数。

### 10.2.4 使用类

客户/服务器模型：客户是使用类的程序，类的声明包括类的方法构成了服务器。

### 10.2.5 修改实现

修改`show()`成员函数，使其按照定点格式输出。

```C++
ios_base::fmtflags orig = cout.setf(ios_base::fixed, ios_base::floatfield);
std::streamsize prec = cout::precision(3);         // 设置定点显示
...
cout.setf(orig, ios_base::floatfield);
cout.precision(prec);								// 恢复原有设置
```

## 10.3 类的构造函数和析构函数

目前位置，虽然构造的类可以使用(.)运算符访问类成员函数，但是还不能像标准类型，比如int那样初始化：

```C++
Stock hot = {"Sukie' Autos, Inc.", 200, 50.25};     // 不能这样做，目前为止
```

书中示例代码的Stock类，它的数据部分的访问状态是私有的，只有成员函数才可以访问，因此需要设计合适的成员函数来完成对象的初始化。这就是类构造函数的作用。

### 10.3.1 声明和定义构造函数

构造函数的原型没有返回值，也没有声明类型，它的参数设置和类数据成员的对应的：

```C++
Stock(const string & co, long n = 0, double pr = 0.0);
```

程序在声明类对象的时候，将自动调用构造函数。

### 10.3.2 使用构造函数

在没有定义构造函数的情况下，下面的语句是非法的：

```C++
Stock hot = {"Sukie's Autos, Inc.", 200, 50.25};
```

因为数据成员是私有的，无法从外部访问，必须使用类成员函数才能访问。通过构造函数可以完成这项任务。

调用构造函数的方法：

```C++
Stock food = Stock("World Cabbage", 250, 1.25);
Stock garment("Furry Mason", 50, 2.5);
Stock *pstock = new Stock("Electroshock Games", 18, 19.0);
```

构造函数不能通过对象来调用。

### 10.3.3 默认构造函数

当不提供显式初始值时，C++会自动提供默认构造函数。

```C++
Stock::Stock() {}
```

**Note**：

1. 当且仅当不提供构造函数时，编译器才会提供默认构造函数，但是不会初始化；

2. 当定义了构造函数后，不提供默认构造函数，那么下面的声明就会出错：

   ```C++
   Stock stock1;
   ```

3. 提供构造函数，有两种方法定义默认构造函数：

   ```C++
   // 为所有参数提供默认参数
   Stock(const string & co = "Error", int n = 0, double pr = 0.0);
   
   // 定义一个不提供任何参数的构造函数
   Stock();
   ```

   以上这两种方式不能同时使用。下面是一种定义的方法：

   ```C++
   Stock::Stock(){
       company = "no name";
       shares = 0;
       share_val = 0.0;
       total_val = 0.0;
   }
   ```

### 10.3.4 析构函数

析构函数负责过期对象的清理工作。

```C++
~Stock();		// 析构函数的原型
Stock::~Stock(){	// 析构函数定义
    cout << "Bye, " << company << "!\n";
}
```

## 10.4 this指针

在现有类的方法中，都是对单独的对象使用类方法，方法中的参数都是普通参数。如果要实现在两个类之间的方法，例如比较两个类中数据的大小，可以把一个类作为参数传入到成员函数中，然后返回值较大的对象的引用。这时就要使用this指针：

```C++
const Stock & Stock::topval(const Stock & s) const
{
    if (s.total_val > total_val)
        return s;
    else
        return *this;
}
```

## 10.6 类作用域

### 10.6.1 作用域为类的常量

```C++
class Bakery{
    private:
    	const int Months = 12;			// 不可以这么做
    	double costs[Months];		
}
```

因为在声明类的时候，并没有创建对象，也就是没有实体，不会分配存储空间。

如果想要定义作用域为类的常量，有两种方法：

```C++
// Method 1
// 定义一个枚举常量
class Bakery{
    private:
    	enum {Months=12};
    	double costs[Months];
}

// Method 2
// 使用static限定符
class Bakery {
    private:
    	static const int Months = 12;
    	double costs[Months];
}
```

枚举的方式：枚举指示创建了一个符号名称，并不会创建类数据成员，对象中并不会包含枚举。

static方式：static的方式将创建一个名为Months常量，该常量存储在静态存储区，而不是对象当中，所以是一个实体。

### 10.6.2 作用域内枚举

传统的枚举存在一些问题，同一类中的两个枚举定义中的枚举量可能发生冲突：

```C++
enum egg{Small, Medium, Large, Jumbo};
enum t_shirt {Small, Medium, Large, Xlarge};
```

上述两个枚举量放在一个类中将会出现错误。解决方法是加上`class`关键字：

```C++
enum class egg {Small, Medium, Large, Jumbo};
enum class t_shirt {Small, Medium, Large, Xlarge};

egg choice = egg::Large;
t_shirt Floyd = t_shirt::Large;
```

在调用时加上枚举名限定就可以了。

 ## 10.7 抽象数据类型（ADT）

数据结构的相关概念。