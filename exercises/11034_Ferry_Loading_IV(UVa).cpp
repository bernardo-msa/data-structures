#include <iostream>
#include <stdexcept>
#include <string>
using namespace std;

#define endl '\n'

template<typename E>
class Queue {
    private:
    void operator=(const Queue&){}
    Queue(const Queue&){}

    public:
    Queue() {}
    virtual ~Queue() {}

    virtual void clear()=0;

    virtual void enqueue(const E& it)=0;

    virtual E dequeue()=0;

    virtual const E& frontValue() const=0;

    virtual int length() const=0;
};

template<typename E>
class Link {
    public:
    E element;
    Link *next;

    Link(const E& elemval, Link* nextval=nullptr)
    {element = elemval; next = nextval;}
    Link(Link* nextval=nullptr) {next=nextval;}
};

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

    virtual int length() const
    {return size;}
};

int main()
{
    int t;
    cin >> t;

    for (int i=0; i<t; ++i)
    {
        LQueue <int> right, left;
        int l, m, total=0, qnt=0;
        cin >> l >> m;

        for (int i=0; i<m; ++i)
        {
            string aux;
            int aux1;

            cin >> aux1 >> aux;

            if (aux=="right")
            {
                right.enqueue(aux1);
            }
            else {left.enqueue(aux1);}
        }

        while ((right.length()!=0)&&(left.length()!=0))
        {
            while(left.length()!=0)
            {
                if (total+left.frontValue() > l) {break;}
                total += left.dequeue();
            }

            total = 0;
            ++qnt;

            while(right.length()!=0)
            {
                if (total+right.frontValue() > l) {break;}
                total += right.dequeue();
            }
        }

        cout << qnt << endl;
    }
}

