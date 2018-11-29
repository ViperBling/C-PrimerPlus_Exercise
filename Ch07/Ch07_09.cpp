#include <iostream>
using namespace std;

const int SLEN = 30;

struct student{
    char fullname[SLEN];
    char hobby[SLEN];
    int ooplevel;
};

int getinfo(student pa[], int n);
void display1(student st);
void display2(const student * ps);
void display3(const student pa[], int n);

int main()
{
    cout << "Enter class size: ";
    int class_size;
    cin >> class_size;
    while (cin.get() != '\n')
        continue;
    auto * ptr_stu = new student [class_size];
    int entered = getinfo(ptr_stu, class_size);
    for (int i = 0; i < entered; i++){
        cout << "Student #" << i+1 << endl;
        display1(ptr_stu[i]);
        display2(&ptr_stu[i]);
        cout << "\n";
    }
    display3(ptr_stu, entered);
    delete [] ptr_stu;
    cout << "Done.\n";

    return 0;
}

int getinfo(student pa[], int n)
{
    int i = 0;

    for (i = 0; i < n; i++){
        cout << "Enter student name: ";
        cin.getline(pa[i].fullname, SLEN);
        if (pa[i].fullname[0] == '\0')
            break;
        cout << "Enter student hobby: ";
        cin.getline(pa[i].hobby, SLEN);
        cout << "Enter student ooplevel: ";
        cin >> pa[i].ooplevel;
        cin.get();
        }
    return i;
}

void display1(student st)
{
    cout << "Fullname: " << st.fullname << endl;
    cout << "Hobby: " << st.hobby << endl;
    cout << "Ooplevel: " << st.ooplevel << endl;
    cout << "\n";
}

void display2(const student * ps)
{
    cout << "Fullname: " << ps->fullname << endl;
    cout << "Hobby: " << ps->hobby << endl;
    cout << "Ooplevel: " << ps->ooplevel << endl;
    cout << "\n";
}

void display3(const student pa[], int n)
{
    for (int i = 0; i < n; i++){
        cout << "Student #" << i+1 << endl;
        cout << "Fullname: " << pa[i].fullname << endl;
        cout << "Hobby: " << pa[i].hobby << endl;
        cout << "Ooplevel: " << pa[i].ooplevel << endl;
        cout << endl;
    }
}