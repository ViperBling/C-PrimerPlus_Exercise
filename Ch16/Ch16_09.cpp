#include <iostream>
#include <vector>
#include <list>
#include <algorithm>
#include <ctime>
using namespace std;

// 测试结果：
// Enter the size of sort array: 100000
// vector sort for 100000: 0.021588
// list sort for 100000: 0.054688
// copy list sort for 100000: 0.02385
//
// Next round, enter the size: 10000000
// vector sort for 10000000: 2.95694
// list sort for 10000000: 6.38709
// copy list sort for 10000000: 3.21732
//
// Next round, enter the size: 100000000
// vector sort for 100000000: 33.433
// list sort for 100000000: 72.0502
// copy list sort for 100000000: 36.0188
//
// Next round, enter the size: q
// Done.



int main()
{

    long size;
    cout << "Enter the size of sort array: ";
    while (cin >> size && size > 0) {
        vector<int> vi0;
        vector<int> vi(size);
        list<int> li(size);
        for (int i = 0; i < size; i++) {
            srand(time(0));
            int tmp = rand() % size + 1;
            vi0.push_back(tmp);
        }
        copy(vi0.begin(), vi0.end(), vi.begin());
        copy(vi0.begin(), vi0.end(), li.begin());
        // time1
        clock_t start1 = clock();
        sort(vi.begin(), vi.end());
        clock_t end1 = clock();
        cout << "vector sort for " << size << ": "
             << (double) (end1 - start1) / CLOCKS_PER_SEC << endl;
        // time2
        clock_t start2 = clock();
        li.sort();
        clock_t end2 = clock();
        cout << "list sort for " << size << ": "
             << (double) (end2 - start2) / CLOCKS_PER_SEC << endl;
        // 重置li内容
        copy(vi0.begin(), vi0.end(), li.begin());
        // time3
        clock_t start3 = clock();
        copy(li.begin(), li.end(), vi.begin());
        sort(vi.begin(), vi.end());
        copy(vi.begin(), vi.end(), li.begin());
        clock_t end3 = clock();
        cout << "copy list sort for " << size << ": "
             << (double) (end3 - start3) / CLOCKS_PER_SEC << endl;
        //
        cout << "\nNext round, enter the size: ";
    }
    cout << "Done.\n";

    return 0;
}