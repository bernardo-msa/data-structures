#ifndef PSEUDO_RANDOM_H
#define PSEUDO_RANDOM_H

#include <vector>
#include <cstdlib>
#include <algorithm>

using namespace std;

inline vector<int> createPermutation(int m) {
    vector<int> perm(m - 1);

    for (int i = 0; i < m - 1; ++i) {
        perm[i] = i + 1;
    }

    for (int i = m - 2; i > 0; --i) {
        int j = rand() % (i + 1);
        swap(perm[i], perm[j]);
    }

    return perm;
}

inline int pseudoRandomProbing(int pos, int i, int m, const vector<int>& perm) {
    if (i == 0)
        return pos;

    return (pos + perm[i - 1]) % m;
}

#endif