//
// Created by tuser on 18-12-24.
//
#include <iostream>
#include "workerqe.h"
using namespace std;




// Worker
Worker::~Worker() {}

void Worker::Data() const {
    cout << "Name: " << fullname << endl;
    cout << "Employee ID: " << id << endl;
}

void Worker::Get() {
    getline(cin, fullname);
    cout << "Enter worker's ID: ";
    cin >> id;
    while (cin.get() != '\n')
        continue;
}


// Waiter
void Waiter::Set() {
    cout << "Enter waiter's name: ";
    Worker::Get();
    Get();
}

void Waiter::Show() const {
    cout << "Category: Waiter\n";
    Worker::Data();
    Data();
    cout << endl;
}

void Waiter::Data() const {
    cout << "Panache rating: " << panache << endl;
}

void Waiter::Get() {
    cout << "Enter waiter's panache rating: ";
    cin >> panache;
    while (cin.get() != '\n')
        continue;
}


// Singer
char * Singer::pv[] = {"other", "alto", "contralto",
                       "soprano", "bass", "baritone", "tenor"};

void Singer::Set() {
    cout << "Enter Singer's name: ";
    Worker::Get();
    Get();
}

void Singer::Show() const {
    cout << "Category: Singer\n";
    Worker::Data();
    Data();
    cout << endl;
}

void Singer::Data() const {
    cout << "Vocal range: " << pv[voice] << endl;
}

void Singer::Get() {
    cout << "Enter number of singer's vocal range: \n";
    int i;
    for (i = 0; i < Vtypes; i++) {
        cout << i << ": " << pv[i] << "   ";
        if (i % 4 == 3)
            cout << endl;
    }
    if (i % 4 != 0)
        cout << endl;
    cin >>voice;
    while (cin.get() != '\n')
        continue;
}


// SingingWaiter
void SingingWaiter::Data() const {
    Singer::Data();
    Waiter::Data();
}

void SingingWaiter::Get() {
    Singer::Get();
    Waiter::Get();
}

void SingingWaiter::Set() {
    cout << "Enter singins waiter's name: ";
    Worker::Get();
    Get();
}

void SingingWaiter::Show() const {
    cout << "Category: Singing Waiter\n";
    Worker::Data();
    Data();
    cout << endl;
}