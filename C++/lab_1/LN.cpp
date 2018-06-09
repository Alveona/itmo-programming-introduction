#include <cstdlib>
#include "LN.h"
#include <cstring>

typedef unsigned char uchar;

static size_t countLength(int num) // ok
{
    size_t l = 0;
    if (num == 0) {
        l = 1;
    } else {
        while (num > 0) {
            num /= 10;
            l++;
        }
    }
    return l;
}

LN::LN(int n) {
    type = INT;
    int temp;
    int abs_n = abs(n);
    l = countLength(abs_n);
    s = n < 0;
    N = (uchar *) malloc(l);
    for (size_t i = 0; abs_n > 0; i++) {
        temp = abs_n % 10;
        abs_n /= 10;
        N[i] = (uchar) temp;
    }
}

LN::LN(const char *p) {
    type = STRING;
    s = (p[0] == '-');
    l = (p[0] == '-') ? strlen(p) - 1 : strlen(p);
    N = (uchar *) malloc(l);
    if (s) {
        for (size_t i = 0; i < l; i++) {
            N[i] = (uchar) p[l - i] - '0';
        }
    } else {
        for (size_t i = 0; i < l; i++) {
            N[i] = (uchar) p[l - i - 1] - '0';
        }
    }

}

LN::LN(const LN &ln) // ok
{
    type = ln.type;
    l = ln.l;
    s = ln.s;
    N = (uchar *) malloc(ln.l);
    memcpy(N, ln.N, ln.l);
}

LN::~LN() {
    if (N)
        free(N);
}

LN LN::operator=(const LN &ln) {
    if (&ln != this) {
        free(N);
    }
    type = ln.type;
    l = ln.l;
    s = ln.s;
    N = (uchar *) malloc(ln.l);
    memcpy(N, ln.N, ln.l);
    return *this;
}

LN &LN::sum_assign(LN &ln) {
    uchar addition = 0;
    size_t min_len = (l <= ln.l) ? l : ln.l;
    uchar temp;
    for (size_t i = 0; i < min_len; i++) {
        temp = N[i] + ln.N[i] + addition;
        addition = (temp >= 10) ? (uchar) (temp / 10) : 0;
        N[i] = (uchar) (temp % 10);
    }
    for (size_t i = min_len; i <= l; i++) {
        if (i == l && addition != 0) {
            this->resize(l + 1);
            N[l - 1] = 1;
            break;
        }
        temp = N[i] + 0 + addition;
        if (temp >= 10) {
            addition = (uchar) (temp / 10);
        } else {
            addition = 0;
        }
        N[i] = (uchar) (temp % 10);
    }
    return *this;
}

LN &LN::sub_assign(LN &ln) {
    uchar taken = 0;
    size_t min_len = (l <= ln.l) ? l : ln.l;
    for (size_t i = 0; i < min_len; i++) {
        if (taken != 0) {
            if (N[i] == 0) {
                N[i] = 9;
                goto v1;
            }
            N[i] -= taken;
        }
        if (N[i] >= ln.N[i]) {
            taken = 0;
            N[i] = (uchar) (N[i] - ln.N[i] % 10);
        } else {
            v1:
            taken = 1;
            N[i] = (uchar) ((N[i] + 10 - ln.N[i]) % 10);
        }
    }
    for (size_t i = min_len; i <= l; i++) {

        if (taken != 0) {
            if (N[i] == 0) {
                N[i] = 9;
                goto v2;
            }
            N[i] -= taken;
        }

        if (N[i] >= 0) {
            taken = 0;
            N[i] = (uchar) (N[i] - 0);
        } else {
            v2:
            taken = 1;
            N[i] = (uchar) ((N[i] + 10 - 0) % 10);
        }
    }
    size_t newlen = 1;
    bool flag = false;
    for (size_t i = l - 1; i > 0; i--) {
        if (N[i] != 0) {
            flag = true;
            newlen++;
        } else {
            if (flag) {
                newlen++;
            }
        }

    }
    if (newlen != l) {
        this->resize(newlen);
    }

    return *this;
}

LN LN::multy(LN &ln) const {
    LN result(0);
    result.l = this->l + ln.l;
    result.resize(result.l);
    for (long long int i = 0; i < result.l; i++) {
        result.N[i] = 0;
    }

    for (long long int i = 0; i < this->l; i++) {
        for (long long int j = 0; j < ln.l; j++) {
            result.N[i + j] += N[i] * ln.N[j];
        }
    }

    for (long long int i = 0; i < result.l - 1; i++) {
        result.N[i + 1] += result.N[i] / 10;
        result.N[i] %= 10;
    }
    while (result.N[result.l - 1] == 0)
        result.l--;
    return result;
}

LN LN::division(LN &ln, int type = 0) {
    LN curvalue(0);
    if(ln == curvalue)
    {
        printf("Division by zero is prohibited\n");
        return curvalue;
    }
    curvalue.l = 1;
    LN result(0);
    result.l = this->l;
    result.resize(result.l);
    for (int i = 0; i < result.l; i++)
        result.N[i] = 0;
    LN temp(10);
    LN zero(0);
    bool temp_s = ln.s;
    ln.s = false;
    int multy_ten = 0;
    int j = 0;
    for (long long int i = 0; i < this->l; i++) {
        if (N[i] == 0 && N[i + 1] == 0) {
            multy_ten++;
        }
    }
    if (multy_ten >= 1) {
        for (int i = 1; i <= multy_ten; i++) {
            for (long long int j = 0; j < this->l - 1; j++) {
                N[j] = N[j + 1];
            }
            l--;
        }
        resize(l);
    }
    for (long long int i = this->l - 1; i >= 0; i--) // size_t !
    {
        j = curvalue.l - 1;
        if (curvalue == zero) {
            curvalue.l++;
        } else {
            curvalue *= temp;
        }

        if (j > 0)
            curvalue.N[l - 1] = this->N[j - 1];

        if (curvalue.N[l] == 0 || curvalue.l == 0) {
            curvalue.resize(curvalue.l + 1);
        }
        curvalue.N[0] = this->N[i];
        curvalue.delete_zeros();

        if (curvalue < ln) {


            if (i != 0) {

                continue;
            } else {
                break;
            }
        }

        int x = 0; // size_t?
        int l = 1;
        int tmp = 10; // just cause o = 10
        while (l <= tmp) // <= ?
        {
            size_t m = (l + tmp) >> 1;
            LN current(1);
            LN temp_m(m);
            current = ln * temp_m;

            if (current < curvalue || current == curvalue) // <= operator
            {
                x = m;
                l = m + 1;
            } else {
                tmp = m - 1;
            }
        }
        result.N[i] = x;
        LN temp_x(x);
        LN temp_result(10);
        temp_result = ln * temp_x;
        curvalue -= temp_result;
    }
    result.delete_zeros();
    if (multy_ten >= 1) {
        for (int i = 1; i <= multy_ten; i++) {
            result *= temp;
        }
    }

    ln.s = temp_s;
    if (type == 0)
        return result;
    if (type == 1)
        return curvalue;
}

LN &LN::delete_zeros() {
    if (l > 1) {
        while (N[l - 1] == 0)
            l--;
    }
    return *this;
}

void LN::resize(size_t length) {

    auto *N_t = (uchar *) realloc(N, length);
    if (N_t)
        N = N_t;
    for (size_t i = length; i > l; i--)
        N[i] = 0;
    l = length;
}

bool LN::operator>(const LN &ln) const {
    if (s > ln.s)
        return false;
    if (s < ln.s)
        return true;
    if (s == ln.s && s == 0) {
        if (l > ln.l)
            return true;
        if (l < ln.l)
            return false;
        if (l == ln.l) {
            for (size_t i = l; i > 0; i--) {
                if (N[i - 1] > ln.N[i - 1]) {
                    return true;
                } else if (N[i - 1] != ln.N[i - 1])
                    return false;
            }
            return false;
        }
    }
    if (s == ln.s && s == 1) {
        if (l > ln.l)
            return false;
        if (l < ln.l)
            return true;
        if (l == ln.l) {
            for (size_t i = l; i > 0; i--) {
                if (N[i - 1] > ln.N[i - 1]) {
                    return false;
                } else if (N[i - 1] != ln.N[i - 1])
                    return true;
            }
            return true;
        }
    }
}

bool LN::greater_bymod(const LN &ln) const {
    if (l > ln.l)
        return true;
    if (l < ln.l)
        return false;
    if (l == ln.l) {
        for (size_t i = l; i > 0; i--) {
            if (N[i - 1] > ln.N[i - 1])
                return true;
        }
        return false;
    }
}

bool LN::equal_bymod(const LN &ln) const {
    if (l != ln.l)
        return false;
    for (size_t i = l; i > 0; i--) {
        if (N[i - 1] != ln.N[i - 1])
            return false;
    }
    return true;
}

bool LN::operator==(const LN &ln) const {
    if (l != ln.l || s != ln.s)
        return false;
    for (size_t i = l; i > 0; i--) {
        if (N[i - 1] != ln.N[i - 1])
            return false;
    }
    return true;
}

bool LN::operator>=(const LN &ln) const {
    if (*this > ln || *this == ln)
        return true;
    return false;
}

LN &LN::operator+=(LN &ln) {
    if (this->greater_bymod(ln) || this->equal_bymod(ln)) {
        if (this->s == ln.s && !this->s) this->sum_assign(ln);
        if (this->s && !ln.s) this->sub_assign(ln);
        if (!this->s && ln.s) this->sub_assign(ln);
        if (this->s == ln.s && this->s) {
            this->sum_assign(ln);
            this->s = true;
        }

    } else {
        LN temp = ln;
        ln = *this;
        *this = temp;
        if (this->s == ln.s && !this->s)
            this->sum_assign(ln);
        if (this->s && !ln.s) this->sub_assign(ln);
        if (!this->s && ln.s) this->sub_assign(ln);
        if (this->s == ln.s && this->s) {
            this->sum_assign(ln);
            this->s = true;
        }
        ln = temp;
    }
    return *this;
}

LN &LN::operator-=(LN &ln) {
    if (this->greater_bymod(ln) || this->equal_bymod(ln)) {
        if (this->s == ln.s && !this->s) this->sub_assign(ln);
        if (this->s && !ln.s) this->sum_assign(ln);
        if (!this->s && ln.s) this->sum_assign(ln);
        if (this->s == ln.s && this->s) {
            this->sub_assign(ln);
            this->s = true;
        }
    } else {
        LN temp = ln;
        ln = *this;
        *this = temp;
        if (this->s == ln.s && !this->s)
            this->sub_assign(ln);
        if (this->s && !ln.s)
            this->sum_assign(ln);
        if (!this->s && ln.s)
            this->sum_assign(ln);
        if (this->s == ln.s && this->s) {
            this->sub_assign(ln);
            this->s = true;
        }
        this->s = !this->s;
        ln = temp;
    }
    return *this;
}

LN LN::operator+(LN &ln) const {
    LN temp = *this;
    return temp += ln;
}

LN LN::operator-(LN &ln) const {
    LN temp = *this;
    return temp -= ln;
}

LN LN::operator*(LN &ln) const {
    LN result(0);
    result = this->multy(ln);
    if (this->s == ln.s)
        result.s = false;
    if (this->s != ln.s)
        result.s = true;
    return result;
}

LN LN::operator/(LN &ln) {
    LN result(0);
    result = this->division(ln, 0);
    if (this->s == ln.s)
        result.s = false;
    if (this->s != ln.s)
        result.s = true;
    return result;
}

LN LN::operator%(LN &ln) {
    LN result(0);
    result = this->division(ln, 1);
    return result;
}

LN &LN::operator*=(LN &ln) {
    *this = *this * ln;
    return *this;
}

LN &LN::operator/=(LN &ln) {
    *this = *this / ln;
    return *this;
}

LN &LN::operator%=(LN &ln) {
    *this = *this % ln;
    return *this;
}

bool LN::operator<(const LN &ln) const {
    return !(*this > ln || *this == ln);
}

void LN::print() const {
    if (s == 1)
        printf("%c", '-');
    for (size_t i = l; i > 0; i--)
        printf("%d", N[i - 1]);
    printf("\n");
}

