#include <iostream>

using namespace std;

template<class T>
struct node
{
    node() {};
    node(T v, node<T>* p) : value {v}, parent {p}, left {}, right {} {};
    T value;
    node<T>* parent;
    node<T>* left;
    node<T>* right;
};

template<class T>
struct bst
{
    bst() : root {nullptr} {};
    node<T>* root;
    node<T>* find(T v)
    {
        auto ptr = root;
        while(ptr)
        {
            if(ptr->value == v)
            {
                return ptr;
            }
            else if(v < ptr->value)
            {
                ptr = ptr->left;
            }
            else
            {
                ptr = ptr->right;
            }
        }
        return nullptr;
    };
    void insert(T v)
    {
        node<T>* parent = nullptr;
        node<T>** ptr = &root;
        while(*ptr)
        {
            parent = *ptr;
            if(v < (*ptr)->value)
            {
                ptr = &((*ptr)->left);
            }
            else
            {
                ptr = &((*ptr)->right);
            }
        }
        *ptr = new node<T>(v, parent);
    };
    node<T>* find_inorder_next(node<T>* p)
    {
        if(p->right)
        {
            auto ptr = p->right;
            while(ptr->left)
            {
                ptr = ptr->left;
            }
            return ptr;
        }
        auto ptr = p->parent;
        auto pre = p;
        while(ptr && ptr->right == pre)
        {
            pre = ptr;
            ptr = ptr->parent;
        }
        if(ptr)
        {
            return ptr;
        }
        return nullptr;
    };
    void delete_value(T v)
    {
        auto ptr = find(v);
        delete_node(ptr);
    };
    void delete_node(node<T>* ptr)
    {
        if(!ptr)
        {
            return;
        }
        auto parent = ptr->parent;
        if(!(ptr->left) && !(ptr->right))
        {
            if(!parent)
            {
                root = nullptr;
            }
            else if(parent->left == ptr)
            {
                parent->left = nullptr;
            }
            else
            {
                parent->right = nullptr;
            }
            delete(ptr);
        }
        else if(ptr->left && ptr->right)
        {
            node<T>* next = find_inorder_next(ptr);
            ptr->value = next->value;
            delete_node(next);
        }
        else if(ptr->left)
        {
            ptr->left->parent = parent;
            if(!parent)
            {
                root = ptr->left;
            }
            else if(parent->left == ptr)
            {
                parent->left = ptr->left;
            }
            else
            {
                parent->right = ptr->left;
            }
            delete(ptr);
        }
        else
        {
            ptr->right->parent = parent;
            if(!parent)
            {
                root = parent->right;
            }
            else if(parent->left == ptr)
            {
                parent->left = ptr->right;
            }
            else
            {
                parent->right = ptr->right;
            }
            delete(ptr);
        }
    };
    void inorder_print(node<T>* r)
    {
        if(!r)
        {
            return;
        }
        inorder_print(r->left);
        cout << ' ' << r->value;
        inorder_print(r->right);
    };
    void preorder_print(node<T>* r)
    {
        if(!r)
        {
            return;
        }
        cout << ' ' << r->value;
        preorder_print(r->left);
        preorder_print(r->right);
    };
    void print()
    {
        inorder_print(root);
        cout << endl;
        preorder_print(root);
        cout << endl;
    };
};

int main()
{
    int n;
    cin >> n;
    char com[10];
    int v;
    auto tree = bst<int>();
    for(int i = 0; i < n; ++i)
    {
        scanf("%s", com);
        if(com[0] == 'i')
        {
            scanf("%d", &v);
            tree.insert(v);
        }
        else if(com[0] == 'f')
        {
            scanf("%d", &v);
            printf(tree.find(v) ? "yes\n" : "no\n");
        }
        else if(com[0] == 'd')
        {
            scanf("%d", &v);
            tree.delete_value(v);
        }
        else
        {
            tree.print();
        }
    }
}
