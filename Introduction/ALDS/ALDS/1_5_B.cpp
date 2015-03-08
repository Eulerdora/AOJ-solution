#include <iostream>

using namespace std;

template <class T>
void print_array(T* xs, int n)
{
    for(int i = 0; i < n; ++i)
    {
        if(i)
        {
            printf(" %d", xs[i]);
        }
        else
        {
            printf("%d", xs[i]);
        }
    }
    cout << endl;
}

template<class T>
int merge(T* xs, int l, int m, int r)
{
    int cnt = 0;
    int temp[r-l];
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
        else if(xs[c1] < xs[c2])
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
    int xs[n];
    for(int i = 0; i < n; ++i)
    {
        int tmp;
        scanf("%d", &tmp);
        xs[i] = tmp;
    }
    int cnt = merge_sort(xs, 0, n);
    print_array(xs, n);
    cout << cnt << endl;
}
