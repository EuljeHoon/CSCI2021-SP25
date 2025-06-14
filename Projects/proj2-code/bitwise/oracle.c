// SPDX-License-Identifier: GPL-3.0-or-later
// Based on Bryan't and O'Halloran's original "datalab" assignment

#include <math.h>

int test_isZero(int x) {
    return x == 0;
}

int test_bitNor(int x, int y) {
    return ~(x | y);
}

int test_leastBitPos(int x) {
    int mask = 1;
    if (x == 0) {
        return 0;
    }

    while (!(mask & x)) {
        mask = mask << 1;
    }
    return mask;
}

int test_copyLSB(int x) {
    return (x & 0x1) ? -1 : 0;
}

int test_distinctNegation(int x) {
    int y = x * -1;
    return x != y;
}

unsigned test_floatAbsVal(unsigned uf) {
    union unsigned_float {
        unsigned u;
        float f;
    };

    union unsigned_float x;
    x.u = uf;

    if (isnan(x.f)) {
        return x.u;
    } else if (((int) x.u) < 0) {
        x.f *= -1;
    }
    return x.u;
}

int test_floatIsLess(unsigned uf, unsigned ug) {
    union unsigned_float {
        unsigned u;
        float f;
    };

    union unsigned_float x;
    x.u = uf;
    union unsigned_float y;
    y.u = ug;
    return x.f < y.f;
}

int test_isAsciiDigit(int x) {
    return (0x30 <= x) && (x <= 0x39);
}

int test_addOK(int x, int y) {
    long long lsum = (long long) x + y;
    return lsum == (int) lsum;
}

int test_isGreater(int x, int y) {
    return x > y;
}

int test_floatFloat2Int(unsigned uf) {
    union unsigned_float {
        unsigned u;
        float f;
    };

    union unsigned_float x;
    x.u = uf;

    if (isnan(x.f)) {
        return 0x80000000;
    } else if (x.f > 0x7FFFFFFF || x.f < ((int) 0x80000000)) {
        return 0x80000000;
    }
    return (int) x.f;
}

int test_absVal(int x) {
    if (x < 0) {
        return -x;
    }
    return x;
}
