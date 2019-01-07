#include <iostream>
#include <iterator>
#include <set>
#include <algorithm>
#include <fstream>
#include <string>

const char * srcfile1 = "mat.dat";
const char * srcfile2 = "pat.dat";
const char * dstfile = "matnpat.dat";

int main()
{
    using namespace std;
    set<string> Mat;
    set<string> Pat;
    set<string> Merge;
    string temp;
    // 定义迭代器，用来将输出复制到屏幕
    ostream_iterator<string, char> out(cout, "\n");

    ifstream fin1(srcfile1);
    ifstream fin2(srcfile2);
    if (!fin1.is_open() || !fin2.is_open()) {
        cerr << "Open source file failed.\n";
        exit(EXIT_FAILURE);
    }
    while (!fin1.eof()) {
        getline(fin1, temp);
        Mat.insert(temp);
    }
    while (!fin2.eof()) {
        getline(fin2, temp);
        Pat.insert(temp);
    }

    cout << "\nHere are Mat's friends: \n";
    copy(Mat.begin(), Mat.end(), out);
    cout << endl;
    cout << "\nHere are Pat's friends: \n";
    copy(Pat.begin(), Pat.end(), out);
    cout << endl;

    cout << "Merge Mat's friends and Pat's friend to one list.\n\n";
    // 合并两个名字列表。因为题目要求创建第三个容器，所以这里使用匿名的迭代器来插入值
    set_union(Mat.begin(), Mat.end(), Pat.begin(), Pat.end(),
              insert_iterator<set<string>> (Merge, Merge.begin()));
    cout << "Write to file " << dstfile << "\n";
    ofstream fout(dstfile);
    // 定义迭代器，只不过不是是将Merge的内容复制到标准输出，而是复制到文件流
    ostream_iterator<string, char> fileout(fout, "\n");
    copy(Merge.begin(), Merge.end(), fileout);
    fin1.close();
    fin2.close();
    fout.close();

    // 重新打开合并后的文件，查看内容
    ifstream fin3(dstfile);
    if (!fin3.is_open()) {
        cerr << "Open merge file " << dstfile << " failed.\n";
        exit(EXIT_FAILURE);
    }
    cout << "After merge:\n";
    while (getline(fin3, temp) && !fin3.eof())
        cout << temp << endl;

    fin3.close();
    cout << "\nDone.\n";

    return 0;
}
