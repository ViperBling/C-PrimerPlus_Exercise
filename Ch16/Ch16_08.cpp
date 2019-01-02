#include <iostream>
#include <iterator>
#include <set>
#include <string>
#include <algorithm>
using namespace std;

int main()
{
    set<string> Mat;
    set<string> Pat;
    set<string> Merge;
    string temp;
    // 定义迭代器，用来将输出复制到屏幕
    ostream_iterator<string, char> out(cout, "\n");

    cout << "Mat, Please enter your friends name (quit to quit): \n";
    cout << "Name: ";
    while (getline(cin, temp) && temp != "quit") {
        Mat.insert(temp);
        cout << "Next, Mat: ";
    }

    cout << "Pat, Please enter your friends name (quit to quit):\n";
    cout << "Name: ";
    while (getline(cin, temp) && temp != "quit") {
        Pat.insert(temp);
        cout << "Next, Pat: ";
    }

    cout << "\nHere are Mat's friends: \n";
    copy(Mat.begin(), Mat.end(), out);
    cout << endl;
    cout << "\nHere are Pat's friends: \n";
    copy(Pat.begin(), Pat.end(), out);
    cout << endl;

    // 合并两个名字列表。因为题目要求创建第三个容器，所以这里使用匿名的迭代器来插入值
    set_union(Mat.begin(), Mat.end(), Pat.begin(), Pat.end(),
              insert_iterator<set<string>> (Merge, Merge.begin()));
    cout << "\nHere are the result of merge: \n";
    copy(Merge.begin(), Merge.end(), out);

    return 0;
}
