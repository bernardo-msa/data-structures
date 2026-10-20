#ifndef LLIST_H
#define LLIST_H

#include <stdexcept>
#include "list.h"
#include "link.h"

template<typename E>
class Llist: public List<E>{
    private:
    Link<E> *head;
    Link<E> *tail;
    Link<E> *curr;
    int cnt;

    void init() 
    {
        curr = tail = head = new Link<E>;
        cnt = 0;
    }

    void removeall()
    {
        while(head != nullptr)
        {
            curr = head;
            head = head->next;
            delete curr;
        }
    }

    public:
    Llist() {init();}

    ~Llist() {removeall();}

    void print() const;

    void clear() override {removeall(); init();}

    void insert (const E& it) override
    {
        curr->next = new Link<E>(it, curr->next);
        if (tail == curr) tail = curr->next;
        cnt++;
    }

    void append(const E& it) override
    {
        tail = tail->next = new Link<E>(it, tail->next);
        cnt++;
    }

    E remove() override
    {
        if(curr->next == nullptr) {throw std::exception();}
        E it = curr->next->element;
        Link<E>* ltemp = curr->next;
        if (tail==curr->next) tail = curr;
        curr-> next = curr->next->next;
        delete ltemp;
        cnt--;
        return it;
    }

    void moveToStart() override {curr=head;}

    void moveToEnd() override {curr=tail;}

    void prev() override
    {
        if (curr == head) return;
        Link<E>* temp = head;
        while (temp->next!=curr) temp=temp->next;
        curr = temp;
    }

    void next() override {if (curr != tail) curr=curr->next;}

    int length() const override {return cnt;}

    int currPos() const  override
    {
        Link<E>* temp = head;
        int i;
        for (i=0; curr!=temp; ++i)
        {temp = temp->next;}
        return i;
    }

    void moveToPos(int pos) override
    {
        if((pos<0)||(pos>this->length())) {throw std::exception();}
        curr = head;
        for (int i=0; i<pos; ++i)
        {curr = curr->next;}
    }

    const E& getValue() const override
    {
        if(curr->next==nullptr) {throw std::exception();}
        return curr->next->element;
    }

};


#endif
