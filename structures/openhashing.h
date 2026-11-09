#ifndef OPEN_HASH_
#define OPEN_HASH_

#include "entry.h"
#include "dictionary.h"
#include "llist.h"
#include <math.h>
#include <stdexcept>

template<typename K, typename E>
class OpenHashing : public Dictionary<K, E> {
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

    E* find(const K& key) override {
        int pos = hash(key);

        H[pos].moveToStart();

        for (int i = 0; i < H[pos].length(); ++i) {
            Entry<K, E>& entry = H[pos].getValue();

            if (entry.key == key) {
                return &entry.element;
            }

            H[pos].next();
        }

        return nullptr;
    }

    E remove(const K& key) override {
        int pos = hash(key);

        H[pos].moveToStart();

        for (int i = 0; i < H[pos].length(); ++i) {
            if (H[pos].getValue().key == key) {
                E value = H[pos].remove().element;
                cnt--;
                return value;
            }

                H[pos].next();
            }

            throw Exception();
    }

    void clear() override {
        for (int i = 0; i < m; ++i) {
            H[i].clear();
        }

        cnt = 0;
    }

    int size() const override {
        return cnt;
    }

};

#endif