#include <iostream>
#include <string>

using namespace std;

struct elem
{
    string name;
    int time;
};

template <class T>
class Queue
{
public:
    Queue(int n) : xs {new T[n]}, maxsize {n}, head {}, tail {0} {};
    void enqueue(T v)
    {
        xs[tail++] = v;
    };
    T dequeue()
    {
        return xs[head++];
    };
    int begin()
    {
        return head;
    };
    int end()
    {
        return tail;
    };
    int size()
    {
        return tail-head;
    };
    T at(int i)
    {
        return xs[i];
    };
private:
    T* xs;
    int maxsize;
    int head;
    int tail;
};

int main()
{
    int n, q;
    cin >> n >> q;
    auto que = Queue<elem>(1000000);
    string str;
    int t;
    for(int i = 0; i < n; ++i)
    {
        cin >> str >> t;
        que.enqueue(elem {str, t});
    }

    int sum = 0;
    while(int s = que.size())
    {
        for(int i = 0; i < s; ++i)
        {
            elem e = que.dequeue();
            if(e.time <= q)
            {
                sum += e.time;
                cout << e.name << ' ' << sum << '\n';
            }
            else
            {
                sum += q;
                e.time -= q;
                que.enqueue(e);
            }
        }
    }
}
