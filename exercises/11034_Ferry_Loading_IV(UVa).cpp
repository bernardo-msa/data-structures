#include <iostream>
#include <stdexcept>
#include <string>
using namespace std;

#define endl '\n'

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

    Link(const E& elemval, Link* nextval=NULL)
    {element = elemval; next = nextval;}
    Link(Link* nextval=NULL) {next=nextval;}
};

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

int main()
{
    int t;
    cin >> t;

    for (int i=0; i<t; ++i)
    {
        LStack<int> right, left;
        int l, m, total=0, qnt=0;
        cin >> l >> m;

        for (int i=0; i<m; ++i)
        {
            string aux;
            int aux1;

            cin >> aux1 >> aux;

            if (aux=="right")
            {
                right.push(aux1);
            }
            else {left.push(aux1);}
        }

        while ((right.length()!=0)&&(left.length()!=0))
        {
            while(left.length()!=0)
            {
                if (total+left.topValue() > l) {break;}
                total += left.pop();
            }

            total = 0;
            ++qnt;

            while(right.length()!=0)
            {
                if (total+right.topValue() > l) {break;}
                total += right.pop();
            }
        }

        cout << qnt << endl;
    }
}

