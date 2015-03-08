#include <iostream>
#include <cstring>

using namespace std;

template<class T>
class heap
{
public:
    heap(int s) : xs {new T[s]}, max_size {s}, size {} {};
    heap(int* ys, int n, int s) : xs {new T[s]}, max_size {s}, size {}
    {
        for(int i = 0; i < n; ++i)
        {
            xs[i] = ys[i];
        }
        size = n;
        for(int i = size/2; i >= 0; --i)
        {
            heapify_down(i);
        }
    };
    void heapify_down(int t)
    {
        int left = t*2 + 1;
        int right = left + 1;
        int max_i = t;
        if(left < size && xs[left] > xs[max_i])
        {
            max_i = left;
        }
        if(right < size && xs[right] > xs[max_i])
        {
            max_i = right;
        }
        if(max_i == t)
        {
            return;
        }
        swap(xs[t], xs[max_i]);
        heapify_down(max_i);
    };
    void heapify_up(int t)
    {
        if(!t)
        {
            return;
        }
        int parent = (t-1)/2;
        if(xs[t] <= xs[parent])
        {
            return;
        }
        swap(xs[t], xs[parent]);
        heapify_up(parent);
    };
    void insert(int v)
    {
        xs[size++] = v;
        heapify_up(size-1);
    };
    T pop()
    {
        T ret = xs[0];
        swap(xs[0], xs[--size]);
        heapify_down(0);
        return ret;
    };
    void print()
    {
        for(int i = 0; i < size; ++i)
        {
            cout << ' ' << xs[i];
        }
        cout << endl;
    };
private:
    T* xs;
    int max_size;
    int size;
};

int main()
{
    auto pque = heap<int>(2000010);
    char com[10];
    int v;
    while(1)
    {
        scanf("%s", com);
        if(strcmp(com, "end") == 0)
        {
            break;
        }
        if(com[0] == 'i')
        {
            scanf("%d", &v);
            pque.insert(v);
        }
        else
        {
            printf("%d\n", pque.pop());
        }
    }
}
