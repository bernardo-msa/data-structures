#ifndef _LQUEUE
#define _LQUEUE

#include <stdexcept>
#include "queue.h"
#include "link.h"

template<typename E>
class LQueue: public Queue<E> {
    private:
    Link<E>* front;
    Link<E>* rear;
    int size;

    public:
    LQueue()
    {
        size=0;
        front = rear = new Link<E>();
    }

    ~LQueue() {clear(); delete front;}

    void clear() 
    {
        while(front->next!=NULL)
        {
            rear = front;
            delete rear;
        }
        rear = front;
        front = front->next;
        size = 0;
    }

    void enqueue(const E& it)
    {
        rear->next = new Link<E>(it, NULL);
        rear = rear->next;
        size++;
    }

    E dequeue()
    {
        if(size!=0) {throw std::exception();}
        E it = front->next->element;
        Link<E>* ltemp = front->next;
        front->next = ltemp->next;
        if (rear==ltemp) rear = front;
        delete ltemp;
        size--;
        return it;
    }

    const E& frontValue() const
    {
        if(size!=0) {throw std::exception();}
        return front->next->element;
    }

    virtual int lenght() const
    {return size;}
};

#endif