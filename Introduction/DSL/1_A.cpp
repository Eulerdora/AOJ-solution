#include <iostream>

using namespace std;
class UFT
{
public:
    UFT(int n) : tree {new int[n]}, r {new int[n]}, s {n}
    {
        int* p = tree;
        int i = 0;
        while(i != s)
        {
            *(p++) = i++;
        }
    };
    int parent(int v)
    {
        if(tree[v] == v)
        {
            return v;
        }
        return tree[v] = parent(tree[v]);
    };
    void unite(int x, int y)
    {
        if(same(x, y))
        {
            return;
        }
        int px = parent(x);
        int py = parent(y);
        int rx = r[px];
        int ry = r[py];
        if(rx > ry)
        {
            tree[py] = px;
        }
        else if(rx < ry)
        {
            tree[px] = py;
        }
        else
        {
            tree[px] = py;
            ++r[py];
        }
    };
    bool same(int x, int y)
    {
        return parent(x) == parent(y);
    }
    void print()
    {
        for(int i = 0; i < s; ++i)
        {
            cout << tree[i] << ' ';
        }
        cout << endl;
    }
private:
    int* tree;
    int* r;
    int s;
};

int main()
{
    ios_base::sync_with_stdio(false);
    int n, q;
    cin >> n >> q;
    UFT uft = UFT(n);
    int com, x, y;
    for(int i = 0; i < q; ++i)
    {
        cin >> com >> x >> y;
        if(com == 0)
        {
            uft.unite(x, y);
        }
        else
        {
            cout << (uft.same(x, y) ? "1" : "0") << endl;
        }
    }
}
