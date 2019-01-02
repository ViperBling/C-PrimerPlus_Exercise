#include <iostream>
#include <set>
#include <algorithm>

using namespace std;

int reduce(long ar[], int n);
void out(long n) {cout << n << " ";}

int main()
{
    long ar[6] = {6, 4, 2, 4, 6, 5};
    cout << "Original array: \n";
    for(auto p : ar)
        cout << p << " ";
    cout << "\nSort and reduce: \n";
    int len = reduce(ar, 6);
    cout << "Length: " << len;

    return 0;
}

int reduce(long ar[], int n) {
    set<long> temp;
    for (int i = 0; i < n; i++)
        temp.insert(ar[i]);
    for_each(temp.begin(), temp.end(), out);
    cout << endl;

    return temp.size();
}