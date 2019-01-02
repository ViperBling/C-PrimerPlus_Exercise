#include <iostream>
#include <set>
#include <algorithm>

using namespace std;

template <class T>
int reduce(T ar[], int n);

template <class T>
void out(T n) { cout << n << " "; }

int main()
{
    long ar1[6] = {6, 4, 2, 4, 6, 5};
    cout << "Original: \n";
    for(auto p : ar1)
        cout << p << " ";
    cout << "\nSort and reduce: \n";
    int len = reduce(ar1, 6);
    cout << "Length: " << len << endl;

    string ar2[6] = {
            "final", "cat", "object",
            "big", "cat", "computer"
    };
    cout << "\nOriginal array: \n";
    for (auto & p : ar2)
        cout << p << " ";
    cout << "\nSort and reduce: \n";
    len = reduce(ar2, 6);
    cout << "Length: " << len;

    return 0;
}

template <class T>
int reduce(T ar[], int n) {
    set<T> temp;
    for (int i = 0; i < n; i++)
        temp.insert(ar[i]);
    for_each(temp.begin(), temp.end(), out<T>);
    cout << endl;

    return temp.size();
}