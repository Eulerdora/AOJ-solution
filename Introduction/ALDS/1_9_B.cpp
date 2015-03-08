#include <iostream>

using namespace std;

template<class T>
class heap
{
public:
    heap(int s) : size {}, max_size {s}, xs {new T[s]} {};
    heap(int* ys, int n, int s) : size {}, max_size {s}, xs {new T[s]}
    {
        for(int i = 0; i < n; ++i)
        {
            xs[i] = ys[i];
        }
        size = n;
        for(int i = size/2; i >= 0; --i)
        {
            max_heapify(i);
        }
    };
    void max_heapify(int t)
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
        max_heapify(max_i);
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
    int n;
    cin >> n;
    int xs[n];
    for(int i = 0; i < n; ++i)
    {
        cin >> xs[i];
    }
    auto h = heap<int>(xs, n, n);
    h.print();
}
