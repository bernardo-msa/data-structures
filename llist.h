#ifndef _LLIST
#define _LLIST

#include "list.h"
#include "Lnode.h"

template<typename E>
class Llist: public List{
    private:
    Link<e> *head;
    Link<e> *tail;
    Link<e> *curr;
    int cnt;

    void init() 
    {
        curr = tail = head = new Link<e>;
        cnt = 0;
    }

    void removeall()
    {
        while(head != NULL)
        {
            curr = head;
            head = head->next;
            delete curr;
        }
    }

    public:
    Llist(int size=100) {init();}

    ~Llist() {removeall();}

    void print() const;

    void clear() {removeall(); init();}

    void insert(const E& it)
    {
        curr->next = new Link<E>(it, curr->next);
        if (tail == curr) tail = curr->next;
        cnt++;
    }

    void append(const E& it)
    {
        tail = tail->next = new Link<E>(it, tail->next);
        cnt++;
    }

    E remove() 
    {
        Assert(curr->next != NULL, "No element");
        E it = curr->next->element;
        Link<E>* ltemp = curr->next;
        if (tail==curr->next) tail = curr;
        curr-> next = curr->next->next;
        delete ltemp;
        cnt--;
        return it;
    }

    void moveToStart() {curr=head;}

    void moveToEnd() {curr=tail;}

    void prev() 
    {
        if (curr == head) return;
        Link<E>* temp = head;
        while (temp->next!=curr) temp=temp->next;
        curr = temp;
    }

    void next() {if (curr != tail) curr=curr->next;}

    int lenght() const {return cnt;}

    int currPos() const 
    {
        Link<E>* temp = head;
        int i;
        for (i=0; curr!=temp; ++i)
        {temp = temp->next;}
        return i;
    }

    void moveToPos(int pos)
    {
        Assert ((pos>=0)&&(pos<=listSize), "Pos out of range");
        curr = head;
        for (int i=0; i<pos; ++i)
        {curr = curr->next;}
    }

    const E& getValue() const
    {
        Assert(curr->next != NULL, "No value");
        return curr->next->element;
    }

};


#endif