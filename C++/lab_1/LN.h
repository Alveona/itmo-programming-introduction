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
private:
    size_t l;
    LN& sum_assign(LN& ln);
    LN& sub_assign(LN& ln);
    LN multy(LN& ln) const;
    LN division(LN& ln, int type);
    bool greater_bymod(const LN& ln) const;
    bool equal_bymod(const LN& ln) const;
    LN& delete_zeros();
    void resize(size_t length);

public:

    explicit LN(int N);
    explicit LN(const char *p);
    LN(const LN& ln);
    ~LN();
    void print() const;
    LN operator=(const LN& ln);
    bool operator>(const LN& ln) const;
    bool operator<(const LN& ln) const;
    bool operator==(const LN& ln) const;
    bool operator>=(const LN& ln) const;
    LN& operator+=(LN& ln);
    LN& operator-=(LN& ln);
    LN& operator*=(LN& ln);
    LN& operator/=(LN& ln);
    LN& operator%=(LN& ln);
    LN operator+(LN& ln) const;
    LN operator-(LN& ln) const;
    LN operator*(LN& ln) const;
    LN operator/(LN& ln);
    LN operator%(LN& ln);
};


#endif //LAB_1_LN_H
