#ifndef AQUEUE_H
#define AQUEUE_H

#include "queue.h"
#include <stdexcept>

template<typename E>
class AQueue: public Queue<E> {
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

    void clear() override {rear=0; front=1;}

    void enqueue(const E& it) override
    {
        if(((rear+2)%maxSize)==front) {throw std::exception();}
        rear = (rear+1)%maxSize;
        listArray[rear]=it;
    }

    E dequeue() override
    {
        if(this->length()==0) {throw std::exception();}
        E it = listArray[front];
        front = (front+1)%maxSize;
        return it;
    }
    
    const E& frontValue() const override
    {
        if(this->length()==0) {throw std::exception();}
        return listArray[front];
    }
    
    int length() const override
    {return ((rear+maxSize)-front+1)%maxSize;}
};

#endif