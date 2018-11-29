#include <iostream>
using namespace std;

const int ArSize = 10;

int Fill_array(double ar[], int size);
void Show_array(double ar[], int size);
void Reverse_array(double ar[], int size);

int main()
{
    double arr[ArSize];
    int size;

    size = Fill_array(arr, ArSize);
    Show_array(arr, size);

    cout << "\n\nArray Reverse: \n";
    Reverse_array(arr, size);
    Show_array(arr, size);

    cout << "\n\nArray Reverse2: \n";
    Reverse_array(arr + 1, size - 2);
    Show_array(arr, size);

    return 0;
}

int Fill_array(double ar[], int size)
{
    double tmp;
    int count = 0;

    cout << "First value: ";
    while (cin >> tmp and count < size){
        ar[count] = tmp;
        cout << "Next value: ";
        count++;
    }
    return count;
}

void Show_array(double ar[], int size)
{
    for (int i = 0; i < size; i++){
        cout << "array[" << i << "] = " << ar[i] << endl;
    }
}

void Reverse_array(double ar[], int size)
{
    double tmp;
    int i, j;

    for (i = 0, j = size - 1; i <= j; i++, j--){
        tmp = ar[i];
        ar[i] = ar[j];
        ar[j] = tmp;
    }
}