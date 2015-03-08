#include <iostream>
#include <vector>
#include <queue>

using namespace std;
struct node
{
    node() {};
    node(int i, int n, int* xs) : id {i}, ns {vector<int>(xs, xs+n)}, d {-1} {};
    int id;
    vector<int> ns;
    int d;
};

void bfs(node* xs, int n, int st)
{
    queue<int> que {};
    bool used[n+1];
    for(int i = 0; i <= n; ++i){
        used[i] = false;
    }
    que.push(st);
    xs[st].d = 0;
    used[st] = true;
    while(que.size())
    {
        int p = que.front();
        que.pop();
        vector<int> ns = xs[p].ns;
        for(auto x : ns)
        {
            if(used[x])
            {
                continue;
            }
            xs[x].d = xs[p].d + 1;
            used[x] = true;
            que.push(x);
        }
    }
}

int main()
{
    int n;
    cin >> n;
    node graph[n+1];
    for(int i = 0; i < n; ++i)
    {
        int id;
        int m;
        cin >> id >> m;
        int xs[m];
        for(int j = 0; j < m; ++j)
        {
            cin >> xs[j];
        }
        graph[id] = node(id, m, xs);
    }
    bfs(graph, n, 1);
    for(int i = 1; i <= n; ++i)
    {
        cout << i << ' ' << graph[i].d << endl;
    }
}
