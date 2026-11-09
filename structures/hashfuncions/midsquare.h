#ifndef MID_SQUARE_H
#define MID_SQUARE_H

#include <cmath>
using namespace std;

int midSquare(int key, int m) {
    long long square = 1LL * key * key;

    int r = 1;
    int aux = m - 1;

    while (aux >= 10) {
        aux /= 10;
        r++;
    }

    int digits = 1;
    long long temp = square;

    while (temp >= 10) {
        temp /= 10;
        digits++;
    }

    int remove = (digits - r) / 2;

    while (remove-- > 0)
        square /= 10;

    long long divisor = 1;

    for (int i = 0; i < r; ++i)
        divisor *= 10;

    return (square % divisor) % m;
}

#endif