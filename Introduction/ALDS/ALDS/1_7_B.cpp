#include <iostream>

using namespace std;
struct node
{
    node() : id {-1}, left {-1}, right {-1}, parent {-1}, sibling {-1}, depth {0}, height {0}, degree {0} {};
    node(int i, int l, int r) : id {i}, left {l}, right {r},
         parent {-1}, sibling {-1}, depth {0},
    height {0}, degree {0}
    {
        if(left >= 0)
        {
            ++degree;
        }
        if(right >= 0)
        {
            ++degree;
        }
    };
    int id;
    int left;
    int right;
    int parent;
    int sibling;
    int depth;
    int height;
    int degree;
};

int const_tree(node* ts, int r)
{
    int left = ts[r].left;
    int right = ts[r].right;
    int height = 0;
    if(left >= 0)
    {
        ts[left].parent = r;
        ts[left].depth = ts[r].depth + 1;
        ts[left].sibling = ts[r].right;
        int h = const_tree(ts, left);
        if(height < h)
        {
            height = h;
        }
    }
    if(right >= 0)
    {
        ts[right].parent = r;
        ts[right].depth = ts[r].depth + 1;
        ts[right].sibling = ts[r].left;
        int h = const_tree(ts, right);
        if(height < h)
        {
            height = h;
        }
    }
    return ts[r].height = (left < 0 && right < 0) ? 0 : height+1;
}

void print_tree(node* ts, int n)
{
    for(int i = 0; i < n; ++i)
    {
        cout << "node " << i << ": ";
        cout << "parent = " << ts[i].parent << ", ";
        cout << "sibling = " << ts[i].sibling << ", ";
        cout << "degree = " << ts[i].degree << ", ";
        cout << "depth = " << ts[i].depth << ", ";
        cout << "height = " << ts[i].height << ", ";
        if(ts[i].parent < 0)
        {
            cout << "root" << endl;
        }
        else if(ts[i].left < 0 && ts[i].right < 0)
        {
            cout << "leaf" << endl;
        }
        else
        {
            cout << "internal node" << endl;
        }
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
        int a, b, c;
        cin >> a >> b >> c;
        node n = node(a, b, c);
        ts[a] = n;
        if(b >= 0)
        {
            fs[b] = true;
        }
        if(c >= 0)
        {
            fs[c] = true;
        }
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
