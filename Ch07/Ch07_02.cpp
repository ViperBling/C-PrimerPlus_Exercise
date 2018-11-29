#include <iostream>
using namespace std;
const int ArSize = 10;

int input(float ar[]);
void show(float ar[], int size);
float aver(const float ar[], int size);

int main()
{
    float golf[ArSize];
    int size;
    float average;

    size = input(golf);
    show(golf, size);
    average = aver(golf, size);
    cout << "Average of Golf score: " << average << endl;

    return 0;
}

int input(float ar[])
{
    float tmp;
    int i = 0;

    cout << "First value: " ;
    while (cin >> tmp and i < ArSize){
        ar[i] = tmp;
        i++;
        cout << "Next value: ";
    }

    return i;
}

void show(float ar[], int size)
{
    cout << "Input array: \n";
    for (int i = 0; i < size; i++){
        cout << ar[i] << " ";
    }
    cout << endl;
}

float aver(const float ar[], int size)
{
    float sum = 0;

    for (int i = 0; i < size; i++){
        sum += ar[i];
    }
    return sum / size;
}