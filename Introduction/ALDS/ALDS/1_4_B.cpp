#include <iostream>

using namespace std;

template<class T>
bool binary_search(T* xs, int st, int ed, T v)
{
    //cout << "v = " << v << " ," << st << ' ' << ed << '\n';
    if(ed-st <= 1)
    {
        return xs[st] == v;
    }
    int mid = (st+ed)/2;
    if(xs[mid] > v)
    {
        return binary_search(xs, st, mid, v);
    }
    else if(xs[mid] < v)
    {
        return binary_search(xs, mid, ed, v);
    }
    else
    {
        return true;
    }
}

int main()
{
    int n;
    cin >> n;
    int xs[n];
    for(int i = 0; i < n; ++i)
    {
        scanf("%d", &xs[i]);
    }
    int q;
    cin >> q;
    int v = 0;
    int cnt = 0;
    for(int i = 0; i < q; ++i)
    {
        scanf("%d", &v);
        if(binary_search(xs, 0, n, v))
        {
            ++cnt;
        }
    }
    cout << cnt << '\n';
}
