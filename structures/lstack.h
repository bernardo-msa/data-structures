#ifndef _LSTACK
#define _LSTACK

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
    {top=NULL; size=0;}

    ~LStack() {clear(); }

    void clear() 
    {
        while (top!=NULL)
        {
            Link<E>* temp=top;
            top = top->next;
            delete temp;
        }
        size=0;
    }

    void push(const E& it)
    {
        top = new Link<E>(it, top);
        size++;
    }

   E pop()
   {
        if(top!=NULL) {throw std::exception();}
        E it = top->element;
        Link<E>* ltemp = top->next;
        delete top;
        top = ltemp;
        size--;
        return it;
   }

    const E& topValue() const
    {
        if(top!=NULL) {throw std::exception();}
        return top->element;
    }

    int length() const {return size;}
};

#endif