//
// Created by tuser on 18-12-24.
//
#include <iostream>
using std::cout;
using std::cin;
using std::endl;
#include "westernshooter.h"

// Person
void Person::Data() const {
    cout << "Name: " << fname << " " << lname << endl;
}

void Person::Get() {
    getline(cin, fname);
    cout << "Enter last name: ";
    getline(cin, lname);
}


// Gunslmger Methods
void Gunslmger::Set() {
    cout << "Enter Guner's first name: ";
    Person::Get();
    Get();
}

void Gunslmger::Show() const {
    cout << "Gunslmger: \n";
    Person::Data();
    Data();
}

void Gunslmger::Data() const {
    cout << "Marks on gun: " << mark << endl;
    cout << "Draw time: " << drawTime << endl;
}

void Gunslmger::Get() {
    cout << "Enter marks on gun: ";
    cin >> mark;
    cout << "Enter draw time: ";
    cin >> drawTime;
    while (cin.get() != '\n')
        continue;
}


// Card Methods
char * Card::valarr[Card::Cvalue] = {"ace", "two", "three", "four", "five",
                                     "six", "seven", "eight", "nine", "ten",
                                     "jack", "queen", "king"};
char * Card::ctarr[Card::Ctype] = {"heart", "spade", "diamond", "club"};

char * Card::getColor() const {
    return ctarr[ct-1];         // ct和value生成随机值的时候都是从1开始，所以这里减1
}

char * Card::getNumber() const {
    return valarr[value-1];
}


// PokerPlayer Methods
void PokerPlayer::Set() {
    cout << "Enter poker player's first name: ";
    Person::Get();
    Get();
}

void PokerPlayer::Show() const {
    cout << "PokerPlayer: \n";
    Person::Data();
    Data();
}

void PokerPlayer::Data() const {
    cout << "Card: " << cd.getColor() << ", " << cd.getNumber() << endl;
}

void PokerPlayer::Get() {
    cout << "Draw a card? (y/n): ";
    char ch;
    cin >> ch;
    if (ch == 'y' or ch == 'Y')
        cd = draw();
    else
        cout << "Operation Abort!\n";
}


// BadDude Methods
void BadDude::Data() const {
    Gunslmger::Data();
    PokerPlayer::Data();
}

void BadDude::Get() {
    Gunslmger::Get();
    PokerPlayer::Get();
}

void BadDude::Set() {
    cout << "Enter BadDude's name: ";
    Person::Get();
    Get();
}

void BadDude::Show() const {
    cout << "BadDue: \n";
    Person::Data();
    Data();
}

double BadDude::Gdraw() {
    return DrawTime();
}

Card & BadDude::Cdraw() {
    return draw();
}