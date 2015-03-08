#include <iostream>

using namespace std;
struct card
{
    char pict;
    int num;
    bool operator<=(card y)
    {
        return num <= y.num;
    };
    bool operator>=(card y)
    {
        return num >= y.num;
    };
    bool operator==(card y)
    {
        return num == y.num;
    };
    bool operator!=(card y)
    {
        return num != y.num;
    };
    bool operator<(card y)
    {
        return operator<=(y) && operator!=(y);
    };
    bool operator>(card y)
    {
        return operator>=(y) && operator!=(y);
    };
};

template<class T>
int partition(T* xs, int p, int r)
{
    T x = xs[r];
    int i = p-1;
    for(int j = p; j < r; ++j)
    {
        if(xs[j] <= x)
        {
            ++i;
            swap(xs[i], xs[j]);
        }
    }
    swap(xs[i+1], xs[r]);
    return i+1;
}

template<class T>
void quick_sort(T* xs, int p, int r)
{
    if(p < r)
    {
        int q = partition(xs, p, r);
        quick_sort(xs, p, q-1);
        quick_sort(xs, q+1, r);
    }
}

template<class T>
int merge(T* xs, int l, int m, int r)
{
    int cnt = 0;
    T temp[r-l];
    int c1 = l;
    int c2 = m;
    int idx = 0;
    while(c1 < m || c2 < r)
    {
        if(c1 == m)
        {
            temp[idx] = xs[c2++];
        }
        else if(c2 == r)
        {
            temp[idx] = xs[c1++];
        }
        else if(xs[c1] <= xs[c2])
        {
            temp[idx] = xs[c1++];
        }
        else
        {
            temp[idx] = xs[c2++];
        }
        ++cnt;
        ++idx;
    }
    for(int i = l; i < r; ++i)
    {
        xs[i] = temp[i-l];
    }
    return cnt;
}

template<class T>
int merge_sort(T* xs, int l, int r)
{
    int cnt = 0;
    if(l+1 < r)
    {
        int mid = (l+r)/2;
        cnt += merge_sort(xs, l, mid);
        cnt += merge_sort(xs, mid, r);
        cnt += merge(xs, l, mid, r);
    }
    return cnt;
}

int main()
{
    int n;
    cin >> n;
    card xs[n];
    card ys[n];
    for(int i = 0; i < n; ++i)
    {
        char ch;
        int v;
        cin >> ch >> v;
        xs[i] = card {ch, v};
        ys[i] = card {ch, v};
    }
    merge_sort(ys, 0, n);
    quick_sort(xs, 0, n-1);
    bool stable = true;
    for(int i = 0; i < n; ++i)
    {
        if(xs[i].pict != ys[i].pict)
        {
            stable = false;
        }
    }
    cout << (stable ? "Stable" : "Not stable") << endl;
    for(int i = 0; i < n; ++i)
    {
        printf("%c %d\n", xs[i].pict, xs[i].num);
    }
}
