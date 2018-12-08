//
// Created by tuser on 18-12-8.
//

#ifndef LIST_H
#define LIST_H

typedef unsigned int Item;

class List {
private:
    static const int MAX = 10;
    Item items[MAX];
    int tail;

public:
    List();
    bool add(Item & item);
    void traverse(void (*pf)(Item &));
    bool isempty() const;
    bool isfull() const;
};

void show(Item &);

#endif // LIST_H
