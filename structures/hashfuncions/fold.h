#ifndef FOLD_H
#define FOLD_H

#include <string>
using namespace std;

int fold(const string& key, int m) {
    int sum = 0;

    for (char c : key) {
        sum += static_cast<unsigned char>(c);
    }

    return sum % m;
}

#endif