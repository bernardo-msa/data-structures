#ifndef QUADRATIC_H
#define QUADRATIC_H

inline int quadraticProbing(int pos, int i, int m) {
    long long offset = 1LL * i * (i + 1) / 2;

    return (pos + offset % m) % m;
}

#endif