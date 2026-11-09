#ifndef ENTRY_
#define ENTRY_

template<typename K, typename E>
class Entry {
    public:
    K key;
    E element;

    Entry(const K& key, const E& element) : key(key), element(element) {};
    Entry() {};
};

#endif 