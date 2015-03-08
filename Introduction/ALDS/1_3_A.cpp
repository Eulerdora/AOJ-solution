#include <iostream>
#include <cstring>
#include <string>
#include <stdexcept>

using namespace std;

bool isoperator(string str)
{
    if(str == "+" || str == "-" || str == "*" || str == "/")
    {
        return true;
    }
    return false;
}

template <typename T>
class Stack
{
public:
    Stack(int s) : xs {new T[s]}, s {} {};
    void push(T v)
    {
        xs[s++] = v;
    };
    T pop()
    {
        return xs[--s];
    };
    int size()
    {
        return s;
    };
    T peek()
    {
        return xs[s-1];
    };
    void print()
    {
        for(int i = 0; i < s-1; ++i)
        {
            cout << xs[i] << ' ';
        }
        cout << xs[s-1] << '\n';
    }
private:
    T* xs;
    int s;
};

void proc(Stack<int>& st, string op)
{
    int a = st.pop();
    int b = st.pop();
    int v = 0;
    if(op == "+")
    {
        v = a+b;
    }
    else if(op == "-")
    {
        v = b-a;
    }
    else if(op == "*")
    {
        v = a*b;
    }
    else if(op == "/")
    {
        v = b/a;
    }
    //cout << "a, b = " << a << ", " << b << '\n';
    //cout << "v = " << v << '\n';
    st.push(v);
}

int main()
{
    string str;
    auto st = Stack<int>(200);
    while(cin >> str)
    {
        if(isoperator(str))
        {
            proc(st, str);
        }
        else
        {
            st.push(stoi(str));
        }
        //cout << "peek = " << st.peek() << '\n';
        //st.print();
    }
    cout << st.peek() << '\n';
}
