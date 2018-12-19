//
// Created by tuser on 18-12-19.
//

#ifndef CD_H
#define CD_H

// 基类
class Cd {
private:
    char * performers;
    char * label;
    int selections;
    double playtime;

public:
    Cd(const char *s1 = "null", const char *s2 = "null", int n = 0, double x = 0.0);
    Cd(const Cd & d);
    virtual ~Cd();
    virtual void Report() const;            // 显示CD的所有信息
    Cd &operator=(const Cd & d);
};

class Classic : public Cd {
private:
    char * prime;

public:
    Classic(const char *p = "null", const char *s1 = "null", const char *s2 = "null",
            int n = 0, double x = 0.0);
    Classic(const Cd & d, const char * p = "null");
    virtual ~Classic();
    virtual void Report() const;
    Classic &operator=(const Classic & cl);
};

#endif // CD_H
