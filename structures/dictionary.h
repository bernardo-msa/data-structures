#ifndef DICT_
#define DICT_

template <typename K, typename E>
class Dictionary {
    public:
    Dictionary() {};

    virtual ~Dictionary() {};

    virtual void clear() = 0;

    virtual void insert(const K& key, const E& value) = 0;

    virtual E remove(const K& key) = 0;

    virtual E find(const K& key) const = 0;

    virtual int size() const = 0;
};

#endif