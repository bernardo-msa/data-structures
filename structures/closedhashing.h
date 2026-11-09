#ifndef CLOSED_HASH_
#define CLOSED_HASH_

#include <vector>
#include <stdexcept>

#include "entry.h"
#include "dictionary.h"

using namespace std;

template<typename K, typename E>
class ClosedHashing : public Dictionary<K, E> {
private:
    int m;
    int cnt;

    vector<Entry<K, E>*> H;
    Entry<K, E>* DELETED;

    int hash(const K& key) const {
        return (key % m + m) % m;
    }

    int probe(const K& key, int i) const {
        return (hash(key) + i) % m;
    }

public:
    ClosedHashing(int sz) : m(sz), cnt(0), H(sz, nullptr) {

        DELETED = new Entry<K, E>();
    }

    ~ClosedHashing() override {
        for (int i = 0; i < m; ++i) {
            if (H[i] != nullptr && H[i] != DELETED) {
                delete H[i];
            }
        }

        delete DELETED;
    }

    void insert(const K& key, const E& el) override {
        int deletedPos = -1;

        for (int i = 0; i < m; ++i) {
            int j = probe(key, i);

            if (H[j] == DELETED) {
                if (deletedPos == -1)
                    deletedPos = j;
            }

            else if (H[j] == nullptr) {
                if (deletedPos != -1)
                    j = deletedPos;

                H[j] = new Entry<K, E>(key, el);
                cnt++;
                return;
            }

            else if (H[j]->key == key) {
                return;
            }
        }

        if (deletedPos != -1) {
            H[deletedPos] = new Entry<K, E>(key, el);
            cnt++;
            return;
        }

        throw exception();
    }

    E* find(const K& key) override {
        for (int i = 0; i < m; ++i) {
            int j = probe(key, i);

            if (H[j] == nullptr) {
                return nullptr;
            }

            if (H[j] != DELETED && H[j]->key == key) {
                return &H[j]->element;
            }
        }

        return nullptr;
    }

    E remove(const K& key) override {
        for (int i = 0; i < m; ++i) {
            int j = probe(key, i);

            if (H[j] == nullptr)
                break;

            if (H[j] != DELETED && H[j]->key == key) {
                E value = H[j]->element;

                delete H[j];
                H[j] = DELETED;

                cnt--;
                return value;
            }
        }

        throw exception();
    }

    void clear() override {
        for (int i = 0; i < m; ++i) {
            if (H[i] != nullptr && H[i] != DELETED) {
                delete H[i];
            }

            H[i] = nullptr;
        }

        cnt = 0;
    }

    int size() const override {
        return cnt;
    }
};

#endif