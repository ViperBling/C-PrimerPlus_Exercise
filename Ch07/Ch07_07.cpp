#include <iostream>
using namespace std;

const int ArSize = 10;

double * fill_array(double * begin, int limit);
void show_array(double * begin, const double * end);
void revalue(double r, double * begin, double * end);

int main()
{
    double proper[ArSize];
    double * end = fill_array(proper, ArSize);
    show_array(proper, end);
    if (end != proper){
        cout << "Enter revaluation factor: ";
        double factor;
        while (!(cin >> factor)){
            cin.clear();
            while (cin.get() != '\n')
                continue;
            cout << "Bad input; Please enter a number: ";
        }
        revalue(factor, proper, end);
        show_array(proper, end);
    }
    cout << "Done.\n";
    cin.get();
    cin.get();

    return 0;
}

double * fill_array(double * begin, int limit)
{
    double tmp;
    int i = 0;
    double * end = begin;

    for (i = 0; i < limit; i++, end++){
        cout << "Enter value #" << i+1 << ": ";
        cin >> tmp;
        if (!cin){
            cin.clear();
            while (cin.get() != '\n')
                continue;
            cout << "Bad input; input process terminated.\n";
            break;
        }
        else if (tmp < 0)
            break;
        *(begin + i) = tmp;
    }

    return end;
}

void show_array(double * begin, const double * end)
{
    double *p = begin;
    int i = 0;

    while (p != end){
        cout << "Property #" << i+1 << ": $" << *p << endl;
        p++;
        i++;
    }
}

void revalue(double r, double * begin, double * end)
{
    double *p = begin;
    int i = 0;

    while (p != end){
        *(begin + i) *= r;
        i++;
        p++;
    }
}