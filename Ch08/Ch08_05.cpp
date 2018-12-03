#include <iostream>

using namespace std;

template <typename T>
T max5(T * array);

int main()
{
    int arr1[5] = {4, 3, 5, 7, 8};
    double arr2[5] = {3.4, 4.6, 7.7, 2.3, 1.8};
    int max1;
    double max2;

    max1 = max5(arr1);
    max2 = max5(arr2);
    cout << "Array1: \n";
    for (auto i: arr1)
        cout << i << " ";
    cout << endl;
    cout << "Array2: \n";
    for (auto i: arr2)
        cout << i << " ";
    cout << endl;
    cout << "Max in array1: " << max1 << endl;
    cout << "Max in array2: " << max2 << endl;

    return 0;
}

template <typename T>
T max5(T * array)
{
    T max = 0;
    for (int i = 0; i < 5; i++){
        if (max < array[i])
            max = array[i];
    }
    return max;
}