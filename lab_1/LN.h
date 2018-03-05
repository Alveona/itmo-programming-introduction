#ifndef LAB_1_LN_H
#define LAB_1_LN_H

#include <cstdio>

typedef unsigned char uchar;
enum Type
{
    INT,
    STRING
};
class LN {
    Type type;
    uchar *N;
    bool s = false;
    size_t l;
public:
    LN& sum_assign(const LN& ln); // should return LN and be private
    explicit LN(int N);
    explicit LN(const char *p);
    LN(const LN& ln);
    ~LN();
    void print() const;
    LN operator=(const LN& ln);
    void resize(size_t length);
    bool operator>(const LN& ln) const;
    bool operator<(const LN& ln) const;
    bool operator==(const LN& ln) const;
    /*LN operator+(const LN& ln);
    LN operator*(const LN& ln);
    LN operator/(const LN& ln);*/

};


#endif //LAB_1_LN_H
