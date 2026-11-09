#include <vector>
#include <stdexcept>
#include <iostream>
#include <string>

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

using namespace std;

template<typename K, typename E>
class ClosedHashing : public Dictionary<K, E> {
private:
    int m;
    int cnt;

    vector<Entry<K, E>*> H;

    int hash(const K& key) const {
        int pos=0;

        for (int i=0; i<key.length(); ++i) {
            pos += (key[i]*(i+1));
        }

        return (19*pos)%101;
    }

public:
    ClosedHashing(int sz)
        : m(sz), cnt(0), H(sz, nullptr) {}

    ~ClosedHashing() override {
        for (int i = 0; i < m; ++i) {
            delete H[i];
        }
    }

    void insert(const K& key, const E& el) override {
        if (find(key) != nullptr)
            return;

        int pos = hash(key);

        for (int i = 0; i < 20; ++i) {
            int j = (pos + i*i + 23*i) % m;

            if (H[j] == nullptr) {
                H[j] = new Entry<K, E>(key, el);
                cnt++;
                return;
            }
        }
    }

        E* find(const K& key) const override {
            int pos = hash(key);

            for (int i = 0; i < 20; ++i) {
                int j = (pos + i*i + 23*i) % m;

                if (H[j] != nullptr && H[j]->key == key) {
                    return &H[j]->element;
                }
            }

            return nullptr;
        }

    E remove(const K& key) override {
        int pos = hash(key);

        for (int i = 0; i < 20; ++i) {
            int j = (pos + i*i + 23*i) % m;

            if (H[j] != nullptr && H[j]->key == key) {
                E value = H[j]->element;

                delete H[j];
                H[j] = nullptr;

                cnt--;
                return value;
            }
        }

        throw exception();
    }

    void clear() override {
        for (int i = 0; i < m; ++i) {
            delete H[i];
            H[i] = nullptr;
        }

        cnt = 0;
    }

    int size() const override {
        return cnt;
    }

    void print() const {
        cout << cnt << '\n';

        for (int i = 0; i < m; ++i) {
            if (H[i] != nullptr) {
                cout << i << ":" << H[i]->key << '\n';
            }
        }
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    int t;
    cin >> t;

    for (int i=0; i<t; ++i) {
        ClosedHashing<string, int> table(101);

        int n;
        cin >> n;

        for (int i=0; i<n; ++i) {
            string aux;
            cin >> aux;

            string op(aux.begin(), aux.begin()+3), key(aux.begin()+4, aux.end());

            if (op=="ADD") {
                table.insert(key, 1);
            }
            else {
                if (table.find(key) != nullptr) {
                    table.remove(key);
                }
            }
        }

        table.print();
    }

    return 0;
}
