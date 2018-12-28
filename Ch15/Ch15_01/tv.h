//
// Created by tuser on 18-12-26.
//

#ifndef TV_H
#define TV_H

#include <iostream>

class Tv;

class Remote {
public:
    enum State{Off, On};
    enum {MinVal, MaxVal = 20};
    enum {Antenna, Cable};
    enum {TV, DVD};
    enum {Regular, Interact};
private:
    int mode;
public:
    int states;
    friend class TV;
    Remote(int m = TV, int n = Regular) : mode(m), states(n) {}
    bool volup(Tv & t);
    bool voldown(Tv & t);
    void onoff(Tv & t);
    void chanup(Tv & t);
    void chandown(Tv & t);
    void set_mode(Tv & t);
    void set_input(Tv & t);
    void set_chan(Tv & t, int c);
    void show_remote_mode() {           // 显示遥控器状态
        if (states == Regular)
            std::cout << "Remote_Mode: Regular";
        else
            std::cout << "Remote_Mode: Interact";
    }
};

class Tv {
public:
    friend class Remote;
    enum State{Off, On};
    enum {MinVal, MaxVal = 20};
    enum {Antenna, Cable};
    enum {TV, DVD};

    Tv(int s = Off, int mc = 125)
            : state(s), volume(5), maxchannel(mc), channel(2), mode(Cable), input(TV) {}
    void onoff() { state = (state == On) ? Off : On; }
    bool ison() const { return state == On; }
    bool volup();
    bool voldown();
    void chanup();
    void chandown();
    void set_mode() { mode = (mode == Antenna) ? Cable : Antenna; }
    void set_input() { input = (input == TV) ? DVD : TV; }
    void settings() const;
    bool set_rmode(Remote & r, int n) {         // 设置遥控器状态
        if (state == Off)
            return false;
        r.states = n;
        return true;
    }

private:
    int state;
    int volume;
    int maxchannel;
    int channel;
    int mode;
    int input;
};

inline bool Remote::volup(Tv &t) { return t.volup(); }
inline bool Remote::voldown(Tv &t) { return t.voldown(); }
inline void Remote::onoff(Tv &t) { t.onoff(); }
inline void Remote::chanup(Tv &t) { t.chanup(); }
inline void Remote::chandown(Tv &t) { t.chandown(); }
inline void Remote::set_mode(Tv &t) { t.set_mode(); }
inline void Remote::set_input(Tv &t) { t.set_input(); }
inline void Remote::set_chan(Tv &t, int c) { t.channel = c; }



#endif // TV_H
