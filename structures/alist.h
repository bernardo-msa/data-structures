#ifndef ALIST_H
#define ALIST_H

#include "list.h"
#include <stdexcept>

template<typename E>
class Alist: public List<E>{
    private:
    int maxSize;
    int listSize;
    int curr;
    E* listArray;

    public:
    Alist(int size=100) {
        maxSize = size;
        listSize = curr = 0;
        listArray = new E[maxSize];
    }

    ~Alist() {delete[] listArray;}

    void clear()
    {
        delete[] listArray;
        listSize = curr = 0;
        listArray = new E[maxSize];
    }

    void insert(const E& it) override
    {
        if(listSize >= maxSize) {throw std::exception();}
        for(int i=listSize; i>curr; --i)
        {listArray[i] = listArray[i-1];}
        listArray[curr] = it;
        listSize++;
    }

    void append(const E& it) override
    {
        if(listSize >= maxSize) {throw std::exception();}
        listArray[listSize++] = it;
    }

    E remove() override
    {
        if((curr<0) || (curr >= listSize)) {throw std::exception();}
        E it = listArray[curr];
        for (int i=curr; i<listSize-1; ++i)
        {listArray[i]=listArray[i+1];}
        --listSize;
        return it;
    }

    void moveToStart() override {curr=0;}

    void moveToEnd() override {curr=listSize;}

    void prev() override {if (curr!=0) curr--;}

    void next() override {if (curr < listSize) curr++;}

    int length() const override {return listSize;}

    int currPos() const override {return curr;}

    void moveToPos(int pos) override
    {
        if((pos<0)||(pos>listSize)) {throw std::exception();}
        curr = pos;
    }

    const E& getValue() const override
    {
        if((curr<0)||(curr>=listSize)) {throw std::exception();}
        return listArray[curr];
    }

};


#endif
