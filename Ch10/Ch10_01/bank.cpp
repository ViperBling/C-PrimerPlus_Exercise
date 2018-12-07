//
// Created by tuser on 18-12-7.
//
#include "bank.h"
#include <string>

Bankac::Bankac(const std::string &m_name, const std::string &m_account, double m_balance) {
    name = m_name;
    account = m_account;
    balance = m_balance;
}

Bankac::Bankac() {
    name = "No Name";
    account = "None";
    balance = 0.0;
}

void Bankac::show() const {
    std::cout << "Name: " << name << std::endl;
    std::cout << "Account: " << account << std::endl;
    std::cout << "Balance: " << balance << std::endl;
}

void Bankac::deposit(double cash) {
    balance += cash;
}

void Bankac::withdraw(double cash) {
    if (balance == 0)
        std::cout << "You have no balance!\n"
                  << "Operation aborted\n";
    else{
        balance -= cash;
    }
}