#ifndef OPEN_HASH_
#define OPEN_HASH_

#include "entry.cpp"
#include "dictionary.h"
#include "llist.h"
#include <math.h>

template<typename K, typename E>
class OpenHashing : public Dictionary {
    private:
    int m;
    int cnt;
    Llist<Entry<K,E>>* H;

    //essa função é a mais básica, porém qualquer função hash pode ser utilizada
    int hash(const K& key) {
        return abs(key)%m;
    }

    public:
    OpenHashing(int sz) : m(sz), cnt(0), H(nullptr) {
        H = new Llist<Entry<K,E>>[m];
    }

    ~OpenHashing() override {
        delete[] H;
    }

    void insert(const K& key, const E& el) {
        if (find(key)==nullptr) {
            int pos = hash(key);
            H[pos].append(Entry<K,E>(key, el));
            cnt++;
        }
    }

    E* find(const K& key) const {
        int pos = hash(key);

        H[pos].moveToStart();

        for (int i=0; )
    }

};

#endif