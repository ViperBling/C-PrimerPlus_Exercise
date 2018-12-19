#include <iostream>
using namespace std;

#include "port.h"
/*
 * a. 方法定义见port.cpp
 * b. 派生类的Show方法需要重新定义以添加新的成员。而重载运算符等不能继承，所以也需要重新定义
 * c. 赋值运算符和重载的<<运算符不能继承，而且<<是友元函数，不能声明为虚函数
 */


int main()
{
    Port port1("Gallo", "tawny", 20);
    cout << port1 << endl;
    VintagePort vp1("Gallo", 24, "Old Velvet", 16);
    VintagePort vp2(vp1);
    cout << vp2 << endl;
    VintagePort vp3;
    vp3 = vp1;
    cout << vp3 << endl;

    Port *p_port;
    p_port = &port1;
    p_port->Show();
    cout << endl;
    p_port = &vp1;
    p_port->Show();
    cout << endl;

    return 0;
}