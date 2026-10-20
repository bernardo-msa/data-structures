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
        Assert(((rear+2)%maxSize)!=front, "Queue is full");
        rear = (rear+1)%maxSize;
        listArray[rear]=it;
    }

    E dequeue()
    {
        Assert(length()!=0, "Queue is empty");
        E it = listArray[front];
        front = (front+1)%maxSize;
        return it;
    }

    const E& frontValue() const
    {
        Assert(length()!=0, "Queue is empty");
        return listArray[front];
    }

    virtual int lenght() const
    {return ((rear+maxSize)-front+1)%maxSize;}
};

#endif