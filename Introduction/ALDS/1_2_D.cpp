#include <iostream>
#include <vector>

using namespace std;

int insertion_sort(int xs[], int n, int g)
{
    int cnt = 0;
    for(int i = g; i < n; ++i)
    {
        //int v = xs[i];
        for(int j = i-g; j >= 0 && xs[j+g] < xs[j]; j-=g)
        {
            ++cnt;
            swap(xs[j+g], xs[j]);
        }
    }
    return cnt;
}

vector<int> gen_g(int n)
{
    auto vec = vector<int> {};
    while(n > 1)
    {
        n /= 2;
        vec.push_back(n);
    }
    if(!vec.size()) vec.push_back(1);
    return vec;
}

int shell_sort(int xs[], int n, vector<int> g)
{
    int cnt = 0;
    vector<int>::iterator it;
    for(it = g.begin(); it != g.end(); ++it)
    {
        cnt += insertion_sort(xs, n, *it);
    }
    return cnt;
}

template <class T>
void print_array(T xs[], int n)
{
    for(int i = 0; i < n; ++i)
    {
        printf("%d\n", xs[i]);
    }
}

void print_vector(vector<int> vec)
{
    vector<int>::iterator it;
    for(it = vec.begin(); it != vec.end(); ++it)
    {
        if(it != vec.begin()) cout << ' ';
        cout << *it;
    }
    cout << '\n';
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
    vector<int> g = gen_g(n);
    int cnt = shell_sort(xs, n, g);

    cout << g.size() << '\n';
    print_vector(g);
    cout << cnt << '\n';
    print_array(xs, n);
}
