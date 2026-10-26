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
    int n, qnt=0;
    bool erro = false;
    string caminho="";
    cin >> n;

    LStack<int> A, B, C;

    for (int i=0; i<n; ++i)
    {
        int aux;
        cin >> aux;
        A.push(aux);
    }

    for (int i=1; i<=n; ++i)
    {
        while(true)
        {    
            if (A.length()!=0)
            {
                if (A.topValue()==i)
                {
                    C.push(i);
                    A.pop();
                    ++qnt;
                    caminho+="A C";
                    break;
                }
                else
                {
                    if (B.length()!=0)
                    {
                        if (B.topValue()==i)
                        {
                            C.push(i);
                            B.pop();
                            ++qnt;
                            caminho+="B C";
                            break;
                        }
                        else
                        {
                            if (A.topValue()<B.topValue())
                            {
                                B.push(A.topValue());
                                A.pop();
                                ++qnt;
                                caminho+="A B";
                                continue;
                            }
                            else
                            {
                                cout << -1;
                                return 0;
                            }
                        }
                    }
                    else
                    {
                        B.push(A.topValue());
                        A.pop();
                        ++qnt;
                        caminho += "A B";
                        continue;
                    }
                }
            }
            else
            {
                if (B.topValue()==i)
                {
                    C.push(i);
                    B.pop();
                    ++qnt;
                    caminho+="B C";
                    break;
                }
                else
                {
                    cout << -1;
                    return 0;
                }
            }
        }
    }

    cout << qnt << endl;

    for (int i=0; i<caminho.length(); i+=3)
    {
        cout << caminho.substr(i, 3) << endl;
    }

    return 0;
}   