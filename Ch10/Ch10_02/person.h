//
// Created by tuser on 18-12-7.
//

#ifndef PERSON_H
#define PERSON_H

#include <iostream>

class Person {
private:
    static const int LIMIT = 25;
    std::string lname;
    char fname[LIMIT];

public:
    Person() {lname = ""; fname[0] = '\0';}
    Person(const std::string & ln, const char * fn = "Heyyou");
    void show() const;
    void FormalShow() const;
};

#endif // PERSON_H
