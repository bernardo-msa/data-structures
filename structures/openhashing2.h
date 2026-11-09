#ifndef OPEN_HASH_
#define OPEN_HASH_

#include <list>
#include <stdexcept>
#include "entry.h"
#include "dictionary.h"

using namespace std;

template<typename K, typename E>
class OpenHashing : public Dictionary<K, E> {
private:
    int m;
    int cnt;
    list<Entry<K, E>>* H;

    int hash(const K& key) const {
        return (key % m + m) % m;
    }

public:
    OpenHashing(int sz) : m(sz), cnt(0), H(nullptr) {
        H = new list<Entry<K, E>>[m];
    }

    ~OpenHashing() override {
        delete[] H;
    }

    OpenHashing(const OpenHashing&) = delete;
    OpenHashing& operator=(const OpenHashing&) = delete;

    void insert(const K& key, const E& el) override {
        if (find(key) == nullptr) {
            int pos = hash(key);
            H[pos].push_back(Entry<K, E>(key, el));
            cnt++;
        }
    }

    E* find(const K& key) override {
        int pos = hash(key);

        for (auto& entry : H[pos]) {
            if (entry.key == key)
                return &entry.element;
        }

        return nullptr;
    }

    E remove(const K& key) override {
        int pos = hash(key);

        for (auto it = H[pos].begin(); it != H[pos].end(); ++it) {
            if (it->key == key) {
                E value = it->element;
                H[pos].erase(it);
                cnt--;
                return value;
            }
        }

        throw out_of_range("Key not found");
    }

    void clear() override {
        for (int i = 0; i < m; ++i)
            H[i].clear();

        cnt = 0;
    }

    int size() const override {
        return cnt;
    }
};

#endif