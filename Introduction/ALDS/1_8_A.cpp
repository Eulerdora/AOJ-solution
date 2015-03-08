#include <iostream>

using namespace std;
struct node
{
    node() : value {}, left {nullptr}, right {nullptr} {};
    node(int v) : value {v}, left {nullptr}, right {nullptr} {};
    int value;
    node* left;
    node* right;
};

struct bst
{
    bst() : root {nullptr} {};
    node* root;
    void insert(int v)
    {
        node** ptr = &root;
        while(*ptr)
        {
            if(v < (*ptr)->value)
            {
                ptr = &((*ptr)->left);
            }
            else
            {
                ptr = &((*ptr)->right);
            }
        }
        *ptr = new node(v);
    };
    void inorder_print(node* ptr)
    {
        if(!ptr)
        {
            return;
        }
        inorder_print(ptr->left);
        cout << ' ' << ptr->value;
        inorder_print(ptr->right);
    };
    void preorder_print(node* ptr)
    {
        if(!ptr)
        {
            return;
        }
        cout << ' ' << ptr->value;
        preorder_print(ptr->left);
        preorder_print(ptr->right);
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
    auto tree = bst();
    for(int i = 0; i < n; ++i)
    {
        scanf("%s", com);
        if(com[0] == 'i')
        {
            scanf("%d", &v);
            tree.insert(v);
        }
        else
        {
            tree.print();
        }
    }
}
