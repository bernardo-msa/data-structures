#include <iostream>
#include <stdexcept>
#include <string>
#define endl '\n'
using namespace std;

template <typename E>
class Stack {
    private:
    void operator=(const Stack&){}
    Stack(const Stack&) {}

    public:
    Stack() {};
    virtual ~Stack() {}

    virtual void clear()=0;

    virtual void push(const E& it)=0;

    virtual E pop()=0;

    virtual const E& topValue() const=0;

    virtual int length() const=0;
};

template<typename E>
class Link {
    public:
    E element;
    Link *next;

    Link(const E& elemval, Link* nextval = nullptr)
        : element(elemval), next(nextval) {}
    Link(Link* nextval = nullptr)
        : next(nextval) {}
};

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

int main() {
    string s;
    int test=0;
    cin >> s;
    
    while(s!="end")
    {
        ++test;
        LStack<char> st[26];
        int qnt=1;
        st[0].push(s[0]);
        
        for (int i=1; i<s.length(); ++i)
        {
            bool encontrou=false;

            if(s[i]>st[0].topValue())
            {
                for (int j=1; j<qnt; ++j)
                {
                    if (st[j].length()==0 || s[i] <= st[j].topValue())
                    {
                        st[j].push(s[i]);
                        encontrou = true;
                        break;
                    }
                }
                if (!encontrou)
                {
                    st[qnt++].push(s[i]);
                }
            }
            else {st[0].push(s[i]);}
        }
        cout << "Case " << test << ": " << qnt << endl;
        cin >> s;
    }

    return 0;
}