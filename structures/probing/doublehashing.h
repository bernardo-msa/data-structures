#ifndef DOUBLE_HASHING_H
#define DOUBLE_HASHING_H

inline int secondHash(int key, int m) {
    return 1 + ((key % (m - 1) + (m - 1)) % (m - 1));
}

inline int doubleHashing(int key, int pos, int i, int m) {
    int step = secondHash(key, m);

    return (pos + 1LL * i * step) % m;
}

#endif