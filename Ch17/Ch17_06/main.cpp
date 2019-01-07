#include <iostream>
#include "file_emp.h"
using namespace std;

const int MAX = 10;

void showMenu();

int main()
{
    abstr_emp *pc[MAX];
    string filename;
    string temp;
    int classtype;
    int index = 0;
    char ch;

    cout << "Enter the filename to save information: ";
    getline(cin, filename);

    // 如果文件存在，说明不是第一次运行，打开并显示内容
    ifstream fin(filename.c_str());
    if (fin.is_open()) {
        cout << "Here are the current contents of the "
             << filename << " file:\n";
        while ((fin >> classtype).get(ch)) {
            switch (classtype) {
                case Employee :
                    pc[index] = new employee;
                    break;
                case Manager :
                    pc[index] = new manager;
                    break;
                case Fink :
                    pc[index] = new fink;
                    break;
                case Highfink :
                    pc[index] = new highfink;
                    break;
                default:
                    break;
            }
            cout << classtype << ": \n";
            pc[index]->getall(fin);
            pc[index]->ShowAll();
            index++;
        }
    }
    fin.close();

    // 首次运行程序，创建文件，并将数据写入
    ofstream fout(filename, ios_base::out | ios_base::app);
    if (!fout.is_open()) {
        cerr << "Open " << filename << " failed.\n";
        exit(EXIT_FAILURE);
    }

    index = 0;
    showMenu();
    while (cin >> ch && ch != 'q' && index < MAX) {
        cin.get();
        switch (ch) {
            case 'a' :
                pc[index] = new employee;
                pc[index]->SetAll();
                break;
            case 'b' :
                pc[index] = new manager;
                pc[index]->SetAll();
                break;
            case 'c' :
                pc[index] = new fink;
                pc[index]->SetAll();
                break;
            case 'd' :
                pc[index] = new highfink;
                pc[index]->SetAll();
                break;
            default :
                cout << "Error choice\n";
                break;
        }
        index++;
        showMenu();
    }
    for (int i = 0; i < index; i++)
        pc[i]->writeall(fout);
    fout.close();
    fin.clear();
    fin.open(filename);
    index = 0;
    if (fin.is_open()) {
        cout << "Here are the current contents of the "
             << filename << " file:\n";
        while ((fin >> classtype).get(ch)) {
            switch (classtype) {
                case Employee :
                    pc[index] = new employee;
                    break;
                case Manager :
                    pc[index] = new manager;
                    break;
                case Fink :
                    pc[index] = new fink;
                    break;
                case Highfink :
                    pc[index] = new highfink;
                    break;
                default:
                    break;
            }
            cout << classtype << endl;
            pc[index]->getall(fin);
            pc[index]->ShowAll();
            index++;
        }
    }
    fin.close();
    cout << "Done.\n";


    return 0;
}

void showMenu() {
    cout << "Which one you want add:\n"
         << "a. Employee        b. Manager\n"
         << "c. Fink            d. Highfink\n"
         << "q. quit\n";
}