#include <iostream>
#include <string>
#include <stdexcept>
using namespace std;

template <typename E>
class List {
    private:
    List(const List&) {}
    void operator= (const List&) {}

    public:
    List() {}
    virtual ~List() {}

    virtual void clear()=0;
    virtual E remove()=0;

    virtual void insert(const E& item)=0;
    virtual void append (const E& item)=0;

    virtual void moveToStart()=0;
    virtual void moveToEnd()=0;
    virtual void moveToPos(int pos)=0;

    virtual void prev()=0;
    virtual void next()=0;

    virtual int length()=0;
    virtual int currPos()=0;

    virtual const E& getValue() const=0;
};

template <typename E>
class Link {
    public:
    E element;
    Link<E>* next;
    
    Link(E it, Link* next=NULL)
    {
        element = it;
        this->next = next;
    }

    Link(Link* next=NULL)
    {
        this->next = next;
    }
};

template <typename E>
class LList : public List<E> {
    private:
    Link<E>* head;
    Link<E>* tail;
    Link<E>* curr;
    int cnt;

    void init() 
    {
        curr = tail = head = new Link<E>();
        cnt = 0;
    }

    void removeall()
    {
        while(curr->next!=NULL)
        {
            Link<E>* ltemp = curr;
            curr = curr->next;
            delete ltemp;
        }
    }

    public:
    LList() {init();}
    ~LList() {removeall();}

    void clear() {removeall(); init();}

    E remove()
    {
        if(curr->next!=NULL) {throw std::exception();}
        E it = curr->next->element;
        if (curr->next->next==NULL)
        {tail = curr->next;}
        Link<E>* ltemp = curr->next;
        curr->next = curr->next->next;
        cnt--;
        delete ltemp;
        return it;
    }

    void insert(const E& item)
    {
        curr->next = new Link<E>(item, curr->next);
        if (tail == curr) {tail = curr->next;}
        cnt++;
    }

    void append(const E& item)
    {
        tail = tail->next = new Link<E>(item);
        cnt++;
    }

    void moveToStart()
    {
        curr = head;
    }

    void moveToEnd()
    {
        curr = tail;
    }

    void moveToPos(int pos)
    {
        if((pos>=0)&&(pos<cnt)) {throw std::exception();}
        curr = head;
        for (int i=0; i<pos; ++i)
        {
            curr = curr->next;
        }
    }

    void prev()
    {
        if(curr!=head) {throw std::exception();}
        Link<E>* ltemp = curr;
        curr = head;
        while (curr->next != ltemp)
        {
            curr = curr->next;
        }
    }

    void next()
    {
        if(curr==tail) {throw std::exception();}
        curr = curr->next;
    }

    int length() {return cnt;}

    int currPos()
    {
        Link<E>* ltemp=curr;
        curr = head;
        int pos=0;
        while(curr !=ltemp)
        {pos++; curr=curr->next;}
        return pos;
    }

    const E& getValue() const
    {
        return curr->next->element;
    }

};

int main(){
    string s;
    while(cin>>s)
    {
        LList<char> list;
        for (int i=0; i<s.length(); ++i)
        {
            if (s[i]=='[')
            {
                list.moveToStart();
                continue;
            }
            else if (s[i]==']')
            {
                list.moveToEnd();
                continue;
            }
            list.insert(s[i]);
            list.next();
        }

        list.moveToStart();

        for (int i=0; i<list.length(); ++i)
        {
            cout << list.getValue();
            list.next();
        }
        cout << endl;
    }
    

    return 0;
}