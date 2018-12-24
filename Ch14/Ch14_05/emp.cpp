//
// Created by tuser on 18-12-24.
//

#include <iostream>
#include "emp.h"
using std::cout;
using std::cin;
using std::endl;


// abstr_emp
void abstr_emp::ShowAll() const {
    cout << "First Name: " << fname << endl;
    cout << "Last Name: " << lname << endl;
    cout << "Job: " << job << endl;
}

void abstr_emp::SetAll() {
    cout << "Enter first name: ";
    getline(cin, fname);
    cout << "Enter last name: ";
    getline(cin, lname);
    cout << "Enter job: ";
    getline(cin, job);
}

abstr_emp::~abstr_emp() {}

std::ostream &operator<<(std::ostream & os, const abstr_emp & e) {
    os << "Name: " << e.fname << ", " << e.lname << endl;
    return os;
}


// manager
void manager::ShowAll() const {
    abstr_emp::ShowAll();
    cout << "Inchargeof: " << inchargeof << endl;
}

void manager::SetAll() {
    abstr_emp::SetAll();
    cout << "Enter inchargeof count: ";
    cin >> inchargeof;
    while (cin.get() != '\n')
        continue;
}


// fink
void fink::ShowAll() const {
    abstr_emp::ShowAll();
    cout << "Reports to: " << reportsto << endl;
}

void fink::SetAll() {
    abstr_emp::SetAll();
    cout << "Reports to whom: ";
    getline(cin, reportsto);
    while (cin.get() != '\n')
        continue;
}


// highfink
void highfink::ShowAll() const {
    abstr_emp::ShowAll();
    cout << "Incharge of: " << manager::InChargeOf() << endl;
    cout << "Reports to: " << fink::ReportsTo() << endl;
}

void highfink::SetAll() {
    abstr_emp::SetAll();
    std::string tmp;
    int tem;
    cout << "Enter the num of incharge: ";
    cin >> tem;
    cin.get();
    cout << "Reports to whom: ";
    getline(cin, tmp);
    ReportsTo() = tmp;
    InChargeOf() = tem;
}