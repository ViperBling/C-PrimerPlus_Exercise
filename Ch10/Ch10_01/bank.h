//
// Created by tuser on 18-12-7.
//

#ifndef BANK_H
#define BANK_H

#include <iostream>

class Bankac{
private:
    std::string name;
    std::string account;
    double balance;

public:
    Bankac(const std::string & m_name, const std::string & m_account,
           double m_balance = 0.0);
    Bankac();
    void show() const;
    void deposit(double cash);
    void withdraw(double cash);
};

#endif // BANK_H
