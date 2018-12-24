//
// Created by tuser on 18-12-24.
//

#ifndef WESTERNSHOOTER_H
#define WESTERNSHOOTER_H

#include <iostream>
#include <cstdlib>
#include <ctime>

// 虚基类
class Person {
private:
    std::string fname;
    std::string lname;

protected:
    virtual void Data() const;
    virtual void Get();

public:
    Person() : fname("None"), lname("None") {}
    Person(const std::string & fn, const std::string & ln)
            : fname(fn), lname(ln) {}

    virtual ~Person() {};
    virtual void Show() const = 0;
    virtual void Set() = 0;
};


// Gunslmger : 派生类
class Gunslmger : virtual public Person {
private:
    double drawTime;        // 拔枪时间
    int mark;               // 枪上的刻痕数

protected:
    double DrawTime() const { return drawTime; }
    void Data() const;
    void Get();

public:
    Gunslmger() : Person(), mark(0), drawTime(0) {}
    Gunslmger(const std::string & fn, const std::string & ln, int m, double d)
                : Person(fn, ln), mark(m), drawTime(d) {}
    Gunslmger(const Person & per, int m, double d)
                : Person(per), mark(m), drawTime(d) {}

    void Set();
    void Show() const;
};


class Card {
protected:
    enum {ace, two, three, four, five, six, seven, eight, nine, ten, jack, queen, king};
    enum {Cvalue = 13};
    enum {heart, spade, diamond, club};     // 四种花色
    enum {Ctype = 4};
private:
    static char *valarr[Cvalue];
    int value;
    static char *ctarr[Ctype];
    int ct;

public:
    Card() : value(ace), ct(heart) {}
    Card(int val, int color) : value(val), ct(color) {}

    // 模拟随机抽牌，返回任意花色面值组合的牌一张
    void randSet() {
        srand(time(0));
        value = rand() % 13 + 1;
        ct = rand() % 4 + 1;
    }
    char *getColor() const;
    char *getNumber() const;
};

// PokerPlayer : 派生类
class PokerPlayer : virtual public Person {
private:
    Card cd;
protected:
    void Data() const;
    void Get();
public:
    PokerPlayer() : cd() {}
    PokerPlayer(const std::string &fn, const std::string &ln, const Card &d)
                : Person(fn, ln), cd(d) {}
    PokerPlayer(const Person &per, const Card &d)
                : Person(per), cd(d) {}

    void Set();
    Card & draw() { cd.randSet(); return cd; }
    void Show() const;
};

class BadDude : public Gunslmger, public PokerPlayer {
protected:
    void Data() const;
    void Get();

public:
    BadDude() {}
    BadDude(const std::string & fn, const std::string & ln, const Card &c, int m = 0, double d = 0)
                : Person(fn, ln), Gunslmger(fn, ln, m, d), PokerPlayer(fn, ln, c) {}
    BadDude(const Person & per, const Card & c, int m = 0, double d = 0)
                : Person(per), Gunslmger(per, m, d), PokerPlayer(per, c) {}
    BadDude(const Gunslmger & gn, const Card & c)
                : Person(gn), Gunslmger(gn), PokerPlayer(gn, c) {}
    BadDude(const PokerPlayer &pp, int m = 0, double d = 0)
                : Person(pp), Gunslmger(pp, m, d), PokerPlayer(pp) {}

    double Gdraw();
    Card & Cdraw();
    void Set();
    void Show() const;
};

#endif // WESTERNSHOOTER_H
