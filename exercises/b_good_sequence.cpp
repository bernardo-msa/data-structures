#include <iostream>
#include <list>
#include <stdexcept>

using namespace std;

template<typename K, typename E>
class Entry {
    public:
    K key;
    E element;

    Entry(const K& key, const E& element) : key(key), element(element) {};
    Entry() {};
};

template <typename K, typename E>
class Dictionary {
    public:
    Dictionary() {};

    virtual ~Dictionary() {};

    virtual void clear() = 0;

    virtual void insert(const K& key, const E& value) = 0;

    virtual E remove(const K& key) = 0;

    virtual E* find(const K& key) const = 0;

    virtual int size() const = 0;
};

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

    E* find(const K& key) const override {
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

    int getRemovals() const {
        int ans = 0;

        for (int i = 0; i < m; ++i) {
            for (const auto& entry : H[i]) {
                int key = entry.key;
                int freq = entry.element;

                if (freq >= key)
                    ans += freq - key;
                else
                    ans += freq;
            }
        }

        return ans;
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    int n;
    cin >> n;

    OpenHashing<int, int> table(1e5);

    for (int i = 0; i < n; ++i) {
        int x;
        cin >> x;

        int* freq = table.find(x);

        if (freq == nullptr) {
            table.insert(x, 1);
        }
        else {
            (*freq)++;
        }
    }

    cout << table.getRemovals() << '\n';

    return 0;
}