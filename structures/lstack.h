#ifndef LSTACK_H
#define LSTACK_H

#include <stdexcept>
#include "stack.h"
#include "link.h"

template <typename E>
class LStack : public Stack<E> {
    private:
    Link<E>* top;
    int size;   

    public:
    LStack() 
    {top=nullptr; size=0;}

    ~LStack() {clear(); }

    void clear() override
    {
        while (top!=nullptr)
        {
            Link<E>* temp=top;
            top = top->next;
            delete temp;
        }
        size=0;
    }

    void push(const E& it) override
    {
        top = new Link<E>(it, top);
        size++;
    }

   E pop() override
   {
        if(top==nullptr) {throw std::exception();}
        E it = top->element;
        Link<E>* ltemp = top->next;
        delete top;
        top = ltemp;
        size--;
        return it;
   }

    const E& topValue() const override
    {
        if(top==nullptr) {throw std::exception();}
        return top->element;
    }

    int length() const override {return size;}
};

#endif