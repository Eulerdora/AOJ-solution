#include <iostream>
#include <stdexcept>
#include <cstring>

using namespace std;

template<class T>
class Node
{
public:
    Node(T v) : Node(v, nullptr, nullptr) {};
    Node(T v, Node<T>* p) : Node(v, p, nullptr) {};
    Node(T v, Node<T>* p, Node<T>* n) : value {v}, prev {p}, next {n} {};
    T get_value()
    {
        return value;
    };
    Node<T>* get_next()
    {
        return next;
    };
    Node<T>* get_prev()
    {
        return prev;
    };
    void set_prev(Node<T>* p)
    {
        prev = p;
    };
    void set_next(Node<T>* p)
    {
        next = p;
    };
private:
    T value;
    Node<T>* prev;
    Node<T>* next;
};

template<class T>
class linkedlist
{
public:
    linkedlist<T>() : head_ptr {nullptr}, last_ptr {nullptr} {};
    void insert(T v)
    {
        auto node = new Node<T>(v, nullptr, head_ptr);
        if(head_ptr)
        {
            head_ptr->set_prev(node);
            head_ptr = node;
        }
        else
        {
            head_ptr = node;
            last_ptr = node;
        }
    };
    void delete_key(T v)
    {
        auto ptr = head_ptr;
        while(ptr)
        {
            if(ptr->get_value() == v)
            {
                Node<T>* prev = ptr->get_prev();
                Node<T>* next = ptr->get_next();
                if(prev)
                {
                    prev->set_next(next);
                }
                else
                {
                    head_ptr = next;
                }
                if(next)
                {
                    next->set_prev(prev);
                }
                else
                {
                    last_ptr = prev;
                }
                delete ptr;
                return;
            }
            ptr = ptr->get_next();
        }
    };
    void deleteFirst()
    {
        if(head_ptr)
        {
            head_ptr = head_ptr->get_next();
            if(head_ptr)
            {
                delete head_ptr->get_prev();
                head_ptr->set_prev(nullptr);
            }
            else
            {
                last_ptr = nullptr;
            }
        }
    };
    void deleteLast()
    {
        if(last_ptr)
        {
            last_ptr = last_ptr->get_prev();
            if(last_ptr)
            {
                delete last_ptr->get_next();
                last_ptr->set_next(nullptr);
            }
            else
            {
                head_ptr = nullptr;
            }
        }
    };
    void print()
    {
        auto ptr = head_ptr;
        while(ptr)
        {
            if(ptr != head_ptr) cout << ' ';
            cout << ptr->get_value();
            ptr = ptr->get_next();
        }
        cout << '\n';
    };
private:
    Node<T>* head_ptr;
    Node<T>* last_ptr;
};

int main()
{
    int n;
    cin >> n;
    char command[20];
    int k;
    auto linkedl = linkedlist<int>();
    while(n--)
    {
        scanf("%s", command);
        if(!strcmp(command, "insert"))
        {
            scanf("%d", &k);
            linkedl.insert(k);
        }
        else if(!strcmp(command, "delete"))
        {
            scanf("%d", &k);
            linkedl.delete_key(k);
        }
        else if(!strcmp(command, "deleteFirst"))
        {
            linkedl.deleteFirst();
        }
        else if(!strcmp(command, "deleteLast"))
        {
            linkedl.deleteLast();
        }
        else
        {
            throw invalid_argument("illegal command");
        }
    }
    linkedl.print();
}
