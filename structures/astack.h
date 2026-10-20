#ifndef _ASTACK
#define _ASTACK

#include "stack.h"

template <typename E>
class AStack : public Stack {
    private:
    int maxSize;
    int top;
    E *listArray;

    public:
    AStack(int size=100) 
    {maxSize=size; top=0; listArray=new E[size];}

    ~AStack() {delete[] listArray;}

    void clear() {top = 0;}

    void push(const E& it)
    {
        if(top!=maxSize) {throw std::exception();}
        listArray[top++] = it;
    }

   E pop()
   {
        if(top!=0) {throw std::exception();}
        return listArray[--top];
   }

    const E& topValue() const
    {
        if(top!=0) {throw std::exception();}
        return listArray[top-1];
    }

    int length() const {return top;}
};

#endif