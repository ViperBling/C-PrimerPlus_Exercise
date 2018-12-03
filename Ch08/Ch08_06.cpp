#include <iostream>
#include <cstring>

using namespace std;

//template <typename T>
//void Show(T arr[], int n);
//template <> void Show(const char * arr[], int n);

template <typename T>
T maxn(T * arr, int n);

// 显式具体化的函数名称一定要是已存在的模板名称
template <> const char * maxn(const char * arr[], int n);

int main()
{
    int arr1[6] = {2, 6, 8, 4, 3, 9};
    double arr2[4] = {2.0, 1.3, 4.6, 1.1};
    const char * arr3[5] = {
            "Hello World",
            "Great! You win!",
            "Double kill",
            "This is a disaster!",
            "Who are you?"
    };
    cout << "Integer array: \n";
    for (auto ele : arr1)
        cout << ele << " ";
    cout << endl;
//    Show(arr1, 6);
    cout << "Max of integer array: " << maxn(arr1, 6) << endl;
    cout << endl;
    cout << "Double array: \n";
    for (auto ele : arr2)
        cout << ele << " ";
    cout << endl;
//    Show(arr2, 4);
    cout << "Max of double array: " << maxn(arr2, 4) << endl;
    cout << endl;
    cout << "String array: \n";
    for (auto ele : arr3)
        cout << ele << endl;
    cout << endl;
//    Show(arr3, 5);
    cout << "Longest string: " << maxn(arr3, 5) << endl;
    cout << "Done.\n";

    return 0;
}

template <typename T>
T maxn(T * arr, int n)
{
    T max = 0;
    for (int i = 0; i < n; i++){
        if (max < arr[i])
            max = arr[i];
    }
    return max;
}

template <> const char * maxn(const char * arr[], int n)
{
    const char * max = arr[0];
    for (int i = 1; i < n; i++){
        if (strlen(max) < strlen(arr[i]))
            max = arr[i];
    }
    return max;
}

//template <typename T>
//void Show(T arr[], int n)
//{
//    for (auto ele : arr)
//        cout << ele << " ";
//    cout << endl;
//}

//template <> void Show(const char * arr[], int n)
//{
//    for (char * ele : &arr)
//        cout << ele << endl;
//    cout << endl;
//}