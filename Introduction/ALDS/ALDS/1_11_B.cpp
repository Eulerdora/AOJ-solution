#include <iostream>
#include <map>
#include <vector>

using namespace std;
struct node
{
    node() {};
    node(int i, int n, int* xs) : id {i}, ns {vector<int>(xs, xs+n)}
    {
        delete xs;
    };
    int id;
    vector<int> ns;
    int in_time;
    int out_time;
};

int dfs(map<int, node*> graph, int time, int id)
{
    node* n = graph[id];
    if(n->in_time > 0)
    {
        return time;
    }
    n->in_time = ++time;
    vector<int> ns = n->ns;
    for(auto it = ns.begin(); it != ns.end(); ++it)
    {
        time = dfs(graph, time, *it);
    }
    n->out_time = ++time;
    return time;
}

int main()
{
    int n;
    cin >> n;
    map<int, node*> graph {};
    int st = 1000000000;
    for(int i = 0; i < n; ++i)
    {
        int id;
        cin >> id;
        st = min(st, id);
        int k;
        cin >> k;
        int* ns = new int[k];
        for(int j = 0; j < k; ++j)
        {
            cin >> ns[j];
        }
        graph[id] = new node(id, k, ns);
    }
    int time = 0;
    for(auto it = graph.begin(); it != graph.end(); ++it)
    {
        pair<int, node*> p = *it;
        if(p.second->in_time)
        {
            continue;
        }
        time = dfs(graph, time, p.first);
    }
    for(auto it = graph.begin(); it != graph.end(); ++it)
    {
        pair<int, node*> p = *it;
        cout << p.first << ' ' << p.second->in_time << ' ' << p.second->out_time << endl;
    }
}
