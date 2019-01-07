//
// Created by tuser on 18-12-24.
//

#ifndef FILE_EMP_H
#define FILE_EMP_H

#include <iostream>
#include <fstream>
#include <string>

enum classkind {Employee, Manager, Fink, Highfink};

// 抽象基类
class abstr_emp {
private:
    std::string fname;
    std::string lname;
    std::string job;
public:
    abstr_emp() : fname("None"), lname("None"), job("None") {}
    abstr_emp(const std::string & fn, const std::string & ln,
              const std::string & j)
            : fname(fn), lname(ln), job(j) {};
    virtual void ShowAll() const;
    virtual void SetAll();
    friend std::ostream &operator<<(std::ostream & os, const abstr_emp & e);
    virtual ~abstr_emp() = 0;
    virtual void getall(std::ifstream & fi) { // 读取文件的虚函数
        std::getline(fi, fname);
        std::getline(fi, lname);
        std::getline(fi, job);
    }
    virtual void writeall(std::ofstream & fo) { // 写入文件的虚函数
        fo << fname << "\n" << lname << "\n" << job << std::endl;
    }
};

// 雇员类
class employee : public abstr_emp {
public:
    employee() : abstr_emp() {}
    employee(const std::string & fn, const std::string & ln,
             const std::string & j) : abstr_emp(fn, ln, j) {}
    virtual void ShowAll() const { abstr_emp::ShowAll(); };
    virtual void SetAll() { abstr_emp::SetAll(); };
    void getall(std::ifstream & fi) { abstr_emp::getall(fi); }
    void writeall(std::ofstream & fo) { fo << Employee << std::endl; abstr_emp::writeall(fo); }
};

// 经理类
class manager : virtual public abstr_emp {
private:
    int inchargeof;             // 管理的abstr_emp数目
protected:
    int InChargeOf() const { return inchargeof; }
    int & InChargeOf() { return inchargeof; }
    void FileChargeOf(std::ofstream & fo) const { fo << inchargeof << std::endl; }
    void FileChargeOf(std::ifstream & fi) { fi >> inchargeof; }

public:
    manager() : abstr_emp(), inchargeof(0) {}
    manager(const std::string & fn, const std::string & ln,
            const std::string & j, int ico = 0)
            : abstr_emp(fn, ln, j), inchargeof(ico) {};
    manager(const abstr_emp & e, int ico) : abstr_emp(e), inchargeof(ico) {};
    manager(const manager & m) : abstr_emp(m) { inchargeof = m.inchargeof; };
    virtual void ShowAll() const;
    virtual void SetAll();
    void getall(std::ifstream & fi) { abstr_emp::getall(fi); fi >> inchargeof; }
    void writeall(std::ofstream & fo) {
        fo << Manager << std::endl;
        abstr_emp::writeall(fo);
        fo << inchargeof << std::endl;
    }
};

class fink : virtual public abstr_emp {
private:
    std::string reportsto;
protected:
    const std::string ReportsTo() const { return reportsto; }
    std::string & ReportsTo() { return reportsto; }
    void FileReportsTo(std::ofstream & fo) const { fo << reportsto << std::endl; }
    void FileReportsTo(std::ifstream & fi) { fi >> reportsto; }

public:
    fink() : abstr_emp(), reportsto("None") {}
    fink(const std::string & fn, const std::string & ln,
         const std::string & j, const std::string & rpo)
            : abstr_emp(fn, ln, j), reportsto(rpo) {};
    fink(const abstr_emp & e, const std::string & rpo) : abstr_emp(e), reportsto(rpo) {};
    fink(const fink & e) : abstr_emp(e) { reportsto = e.reportsto; };
    virtual void ShowAll() const;
    virtual void SetAll();
    void getall(std::ifstream & fi) {
        abstr_emp::getall(fi);
        std::getline(fi, reportsto);
    }
    void writeall(std::ofstream & fo) {
        fo << Fink << std::endl;
        abstr_emp::writeall(fo);
        fo << reportsto << std::endl;
    }
};

class highfink : public manager, public fink {
public:
    highfink() {}
    highfink(const std::string & fn, const std::string & ln,
             const std::string & j, const std::string & rpo, int ico)
            : abstr_emp(fn, ln, j), manager(fn, ln, j, ico), fink(fn, ln, j, rpo) {};
    highfink(const abstr_emp & e, const std::string & rpo, int ico)
            : abstr_emp(e), manager(e, ico), fink(e, rpo) {};
    highfink(const fink & f, int ico) : abstr_emp(f), manager(f, ico), fink(f) {};
    highfink(const manager & m, const std::string & rpo) : abstr_emp(m), manager(m), fink(m, rpo) {};
    highfink(const highfink & h) : abstr_emp(h), manager(h), fink(h) {};
    virtual void ShowAll() const;
    virtual void SetAll();
    void getall(std::ifstream & fi) {
        abstr_emp::getall(fi);
        manager::FileChargeOf(fi);
        fink::FileReportsTo(fi);
    }
    void writeall(std::ofstream & fo) {
        fo << Highfink << std::endl;
        abstr_emp::writeall(fo);
        manager::FileChargeOf(fo);
        fink::FileReportsTo(fo);
    }
};

#endif // FILE_EMP_H