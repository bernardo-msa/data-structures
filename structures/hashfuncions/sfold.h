#ifndef SFOLD_H
#define SFOLD_H

#include <string>
using namespace std;

int sfold(const string& key, int m) {
    unsigned int sum = 0;

    for (int i = 0; i < key.length(); i += 4) {
        unsigned int mult = 1;

        for (int j = 0; j < 4 && i + j < key.length(); ++j) {
            sum += static_cast<unsigned char>(key[i + j]) * mult;
            mult *= 256;
        }
    }

    return sum % m;
}

#endif