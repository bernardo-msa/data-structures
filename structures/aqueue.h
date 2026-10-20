#ifndef _AQUEUE
#define _AQUEUE

#include "queue.h"

template<typename E>
class AQueue: public Queue {
    private:
    int maxSize;
    int front;
    int rear;
    E* listArray;

    public:
    AQueue(int size=100)
    {
        maxSize=size+1;
        rear=0; front=1;
        listArray=new E[maxSize];
    }

    ~AQueue() {delete[] listArray;}

    void clear() {rear=0; front=1;}

    void enqueue(const E& it)
    {
        if(((rear+2)%maxSize)!=front) {throw std::exception();}
        rear = (rear+1)%maxSize;
        listArray[rear]=it;
    }

    E dequeue()
    {
        if(length()!=0) {throw std::exception();}
        E it = listArray[front];
        front = (front+1)%maxSize;
        return it;
    }

    const E& frontValue() const
    {
        if(length()!=0) {throw std::exception();}
        return listArray[front];
    }

    virtual int lenght() const
    {return ((rear+maxSize)-front+1)%maxSize;}
};

#endif