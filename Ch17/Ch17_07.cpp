#include <iostream>
#include <fstream>
#include <string>
#include <iterator>
#include <vector>
#include <algorithm>
using namespace std;

class Store {
    ofstream & fo;
public:
    Store(ofstream & os) : fo(os) {}
    void operator()(const string & st) {
        size_t len = st.size();                     // 获取字符串长度
        fo.write((char *) &len, sizeof(size_t));    // 将字符串长度存储到文件中
        fo.write(st.data(), len);                   // 将字符串内容存储到文件中
    }
};

void ShowStr(const string &);
void GetStrs(ifstream &, vector<string> &);

int main()
{
    vector<string> vostr;
    string temp;

    cout << "Enter strings (empty line to quit):\n";
    while (getline(cin, temp) && temp[0] != '\0')
        vostr.push_back(temp);
    cout << "Here is your input.\n";
    for_each(vostr.begin(), vostr.end(), ShowStr);

    ofstream fout("string.dat", ios_base::out | ios_base::binary);
    for_each(vostr.begin(), vostr.end(), Store(fout));
    fout.close();

    vector<string> vistr;
    ifstream fin("string.dat", ios_base::in | ios_base::binary);
    if (!fin.is_open()) {
        cerr << "Could not open file for input.\n";
        exit(EXIT_FAILURE);
    }
    GetStrs(fin, vistr);
    cout << "\nHere are the strings read from the file:\n";
    for_each(vistr.begin(), vistr.end(), ShowStr);

    return 0;
}

void ShowStr(const string & st) {
    cout << st << endl;
}

void GetStrs(ifstream & fi, vector<string> & str) {
    size_t len;
    // 下面的循环读取len的信息到流中
    while (fi.read((char *) &len, sizeof(size_t))) {
        char *s = new char[len];
        fi.read(s, len);
        s[len + 1] = '\0';
        str.push_back(s);
    }
}