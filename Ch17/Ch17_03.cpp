#include <iostream>
#include <fstream>

int main(int argc, char * argv[])
{
    using namespace std;

    if (argc <= 2) {
        cout << "Usage: " << argv[0] << " srcfile dstfile\n";
        exit(EXIT_FAILURE);
    }
    // 打开源文件，使用输入流，把源文件内容读入到输入流中
    ifstream fin(argv[1]);
    if (!fin.is_open()) {
        cerr << "Open " << argv[1] << " failed!\n";
        exit(EXIT_FAILURE);
    }
    // 打开目的文件，使用输出流，将流内容输入到文件中
    ofstream fout(argv[2]);
    if (!fout.is_open()) {
        cerr << "Open " << argv[2] << " failed!\n";
        exit(EXIT_FAILURE);
    }

    char c;
    while (fin.get(c))    // 从输入流中读取内容，直到文件结尾
        fout.put(c);      // 把从输入流中读取的内容输出到输出流中

    cout << "Done.\n";
    fout.close();
    fin.close();

    return 0;
}
