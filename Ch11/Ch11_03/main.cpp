#include <iostream>
#include <cstdlib>
#include <ctime>
#include "vect.h"

double max(const double ar[], int n);
double min(const double ar[], int n);
double aver(const double ar[], int n);

int main()
{
    using namespace std;
    using  VECTOR::Vector;
    srand(time(0));
    double direction;
    Vector step;
    Vector result(0.0, 0.0);
    double steps = 0;
    double target;
    double dstep;
    int times;
    double Max, Min, Aver;

    cout << "Enter target distance (q to quit): ";
    while (cin >> target) {
        cout << "Enter step length: ";
        if (!(cin >> dstep))
            break;
        cout << "Enter test times: ";
        cin >> times;
        double stepsar[times];
        for (int i = 0; i < times; i++){
            while (result.magval() < target) {
                direction = rand() % 360;
                step.reset(dstep, direction, Vector::POL);
                result = result + step;
                // 累加步数
                steps++;
            }
            stepsar[i] = steps;
            steps = 0;
            result.reset(0.0, 0.0);
        }
        Max = max(stepsar, times);
        Min = min(stepsar, times);
        Aver = aver(stepsar, times);

        cout << "After " << times << " test, \n"
             << "Max step: " << Max << endl;
        cout << "Min step: " << Min << endl;
        cout << "Average step: " << Aver << endl;

        cout << "Enter target distance (q to quit): ";
        Max = Min = Aver = 0.0;
    }
    cout << "Bye!\n";
    cin.clear();
    while (cin.get() != '\n')
        continue;

    return 0;
}

double max(const double ar[], int n)
{
    double max = ar[0];
    for (int i = 0; i < n; i++){
        if (ar[i] > max)
            max = ar[i];
    }
    return max;
}

double min(const double ar[], int n)
{
    double min = ar[0];
    for (int i = 0; i < n; i++){
        if (ar[i] < min)
            min = ar[i];
    }
    return min;
}

double aver(const double ar[], int n)
{
    double sum = 0.0;
    for (int i = 0; i < n; i++)
        sum += ar[i];
    return sum / n;
}