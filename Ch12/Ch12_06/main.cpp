#include <iostream>
#include <cstdlib>
#include <ctime>
#include "queue.h"

const int MIN_PER_HR = 60;

bool newcustomer(double x) { return (std::rand() * x / RAND_MAX < 1); }

int main()
{
    using namespace std;
    using std::ios_base;

    std::srand(time(0));

    cout << "Case Study: Bank of Heather Automatic Teller\n";
    cout << "Enter maximum size of queue: ";
    int qs;
    cin >> qs;
    Queue line1(qs);
    Queue line2(qs);

    cout << "Enter the number of simulation hours: ";
    int hours;
    cin >> hours;
    // 设置循环次数，每分钟一次
    long cyclelimit = MIN_PER_HR * hours;

    cout << "Enter the average number of customers per hour: ";
    double perhour;
    cin >> perhour;
    double min_per_cust;                        // 客户到达的平均时间间隔
    min_per_cust = MIN_PER_HR / perhour;

    Item temp;                                  // 新用户
    long turnaways = 0;                         // 满队离开的用户
    long customers = 0;                         // 加入队列的用户
    long served = 0;                            // 模拟中服务的用户数量
    long sum_line = 0;                          // 累计的队列长度
    int wait_time1 = 0;                          // 新用户处理所需的时间
    int wait_time2 = 0;
    long line_wait = 0;                         // 累计的时间

    for (int cycle = 0; cycle < cyclelimit; cycle++) {
        if (newcustomer(min_per_cust)) {        // 新用户到达
            if (line1.isfull() && line2.isfull())
                turnaways++;                    // 队满，用户转身离开
            else {
                customers++;
                temp.set(cycle);                // cycle = 用户到达的时间
                if (line1.queuecount() <= line2.queuecount())
                    line1.enqueue(temp);
                else
                    line2.enqueue(temp);
            }
        }
        if (wait_time1 <= 0 && !line1.isempty()) {
            line1.dequeue(temp);                 // 前一个用户处理完成
            wait_time1 = temp.ptime();           // 设置等待时间为处理时间
            line_wait += cycle - temp.when();   // 增加累计时间
            served++;                           // 增加已服务用户计数
        }
        if (wait_time1 > 0)
            wait_time1--;
        sum_line += line1.queuecount();

        if (wait_time2 <= 0 && !line2.isempty()) {
            line2.dequeue(temp);                 // 前一个用户处理完成
            wait_time2 = temp.ptime();           // 设置等待时间为处理时间
            line_wait += cycle - temp.when();   // 增加累计时间
            served++;                           // 增加已服务用户计数
        }
        if (wait_time2 > 0)
            wait_time2--;
        sum_line += line2.queuecount();
    }

    if (customers > 0) {
        cout << "customers accepted: " << customers << endl;
        cout << "  customers served: " << served << endl;
        cout << "         turnaways: " << turnaways << endl;
        cout << "average queue size: ";
        cout.precision(2);
        cout.setf(ios_base::fixed, ios_base::floatfield);
        cout << (double) sum_line / cyclelimit << endl;
        cout << " average wait time: "
             << (double) line_wait / served << " minutes\n";
    }
    else
        cout << "No customers!\n";
    cout << "Done!\n";

    return 0;
}

