#include <iostream>
#include <vector>

using namespace std;
struct node
{
    node() : children {vector<int>()}, parent {-1}, depth {} {};
    node(vector<int> cs) : children {cs}, parent {-1}, depth {} {};
    vector<int> children;
    int parent;
    int depth;
};

void const_tree(node* xs, int r)
{
    auto cs = xs[r].children;
    for(auto it = cs.begin(); it != cs.end(); ++it)
    {
        xs[*it].parent = r;
        xs[*it].depth = xs[r].depth+1;
        const_tree(xs, *it);
    }
}

void print_tree(node* xs, int n)
{
    for(int i = 0; i < n; ++i)
    {
        printf("node %d: parent = %d, depth = %d, ", i, xs[i].parent, xs[i].depth);
        if(xs[i].parent < 0)
        {
            printf("root");
        }
        else if(xs[i].children.size() > 0)
        {
            printf("internal node");
        }
        else
        {
            printf("leaf");
        }
        printf(", [");
        for(auto it = xs[i].children.begin(); it != xs[i].children.end(); ++it)
        {
            if(it == xs[i].children.begin())
            {
                printf("%d", *it);
            }
            else
            {
                printf(", %d", *it);
            }
        }
        printf("]\n");
    }
}

int main()
{
    int n;
    cin >> n;
    node ts[n];
    auto fs = new bool[n];
    for(int i = 0; i < n; ++i)
    {
        int id;
        int cn;
        cin >> id >> cn;
        vector<int> cs {};
        for(int j = 0; j < cn; ++j)
        {
            int temp;
            cin >> temp;
            fs[temp] = true;
            cs.push_back(temp);
        }
        ts[id] = node(cs);
    }
    int root = -1;
    for(int i = 0; i < n; ++i)
    {
        if(!fs[i])
        {
            root = i;
            break;
        }
    }
    const_tree(ts, root);
    print_tree(ts, n);
}
