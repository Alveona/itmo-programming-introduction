#include <cstdlib>
#include "LN.h"
#include <cstring>
typedef unsigned char uchar;
static size_t countLength(int num) // ok
{
    size_t l = 0;
    if(num == 0) {
        l = 1;
    }
    else
    {
        while(num > 0)
        {
            num/=10;
            l++;
        }
    }
    return l;
}
LN::LN(int n) { // ok
    printf("int constructor called\n");
    type = INT;
    int temp;
    int abs_n = abs(n);
    l = countLength(abs_n);
    s = n < 0;
    N = (uchar*)malloc(l);
    for(size_t i = 0; abs_n > 0; i++)
    {
        temp = abs_n%10;
        abs_n/=10;
        N[i] = temp;
    }
    /*while(aN_t > 0)
    {
        t = aN_t%10;
        aN_t/=10;
        N[i] = t;
        i++;
    }*/
}
LN::LN(const char *p) { // ok
    printf("string constructor called\n");
    type = STRING;
    s = (p[0] == '-');
    l = (p[0] == '-') ? strlen(p) - 1 : strlen(p);
    N = (uchar*)malloc(l);
    if(s)
    {
        for(size_t i = 0; i < l; i++)
        {
            N[i] = p[l-i] - '0';
        }
    }
    else
    {
        for(size_t i = 0; i < l; i++)
        {
            N[i] = p[l-i-1] - '0';
        }
    }

}
LN::LN(const LN& ln) // ok
{
    printf("copy constructor called\n");
    type = ln.type;
    l = ln.l;
    s = ln.s;
    N = (uchar*)malloc(ln.l);
    memcpy(N, ln.N, ln.l);
}
LN::~LN() { // ok
    printf("destructor called\n");
    if(N)
        free(N);
}
LN LN::operator=(const LN& ln)
{
    printf(" = called\n");
    if(&ln != this)
    {
        free(N);
    }
    type = ln.type;
    l = ln.l;
    s = ln.s;
    N = (uchar*)malloc(ln.l);
    memcpy(N, ln.N, ln.l);
    return *this;
}
LN& LN::sum_assign(const LN &ln) {
    size_t l_new = (l > ln.l) ? l : ln.l;
    printf("new length : %zu\n", l_new);
    this->resize(l_new);
    return *this;
}
void LN::resize(size_t length) {
    //uchar* N_t = (uchar*)malloc(length);
    auto* N_t = (uchar*)realloc(N, length);
    if(N_t)
        N = N_t;
    for(size_t i = length; i > l; i--)
        N[i] = 0;
    //realloc
    //memcpy(N_t, N, l);
    //N = N_t;
    l = length;
}
bool LN::operator>(const LN &ln) const{
    if(s > ln.s)
        return false;
    if(s < ln.s)
        return true;
    if(s == ln.s && s == 0) {
        if (l > ln.l)
            return true;
        if (l < ln.l)
            return false;
        if (l == ln.l) {
            for (size_t i = l - 1; i > 0; i--) {
                if (N[i] > ln.N[i])
                    return true;
            }
            return false;
        }
    }
    if(s == ln.s && s == 1) {
        if (l > ln.l)
            return false;
        if (l < ln.l)
            return true;
        if (l == ln.l) {
            for (size_t i = l - 1; i > 0; i--) {
                if (N[i] > ln.N[i])
                    return false;
            }
            return true;
        }
    }
}
bool LN::operator==(const LN &ln) const {

}
bool LN::operator<(const LN &ln) const{
    bool isGreater = *this > ln; // add '='
    return isGreater? false : true;
}
void LN::print() const {
    printf("s : %d\n", s);
    printf("l = %zu\n", l);
    if(s == 1)
        printf("%c", '-');
    for(size_t i = l; i > 0; i--)
        printf("%d", N[i - 1]);
    /*else
    {
        for(size_t i = l; i > 0; i--)
            printf("%c", N[i - 1]);
    }*/
    printf("\n");
}

