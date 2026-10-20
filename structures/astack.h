#ifndef ASTACK_H
#define ASTACK_H

#include <stdexcept>
#include "stack.h"

template <typename E>
class AStack : public Stack<E> {
    private:
    int maxSize;
    int top;
    E *listArray;

    public:
    AStack(int size=100) 
    {maxSize=size; top=0; listArray=new E[size];}

    ~AStack() {delete[] listArray;}

    void clear() override {top = 0;}

    void push(const E& it) override
    {
        if(top>=maxSize) {throw std::exception();}
        listArray[top++] = it;
    }

   E pop() override
   {
        if(top==0) {throw std::exception();}
        return listArray[--top];
   }

    const E& topValue() const override
    {
        if(top==0) {throw std::exception();}
        return listArray[top-1];
    }

    int length() const override {return top;}
};

#endif