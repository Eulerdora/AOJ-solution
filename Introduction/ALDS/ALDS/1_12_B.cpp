#include <iostream>
#include <vector>
#include <queue>

#define INF 1000000000
using namespace std;

struct edge {
    int from;
    int to;
    int w;
};
struct node {
    node() : id {-1}, d {INF}, ns {} {};
    node(int i, vector<edge>& vec) : id {i}, d {INF}, ns {vec} {};
    int id;
    int d;
    vector<edge> ns;
};

struct node_s {
    int id;
    int d;
};

vector<int> dijkstra(node* graph, int n, int st){
    auto ds = vector<int>(n, INF);
    auto comp = [](node_s* x, node_s* y){return x->d > y->d;};
    priority_queue<node_s*, vector<node_s*>, decltype(comp)> que(comp);
    node_s* start = new node_s {graph[st].id, 0};
    que.push(start);
    while(que.size()){
        node_s* n = que.top();
    //    cout << n->id << ' ' << n->d << endl;
        que.pop();
        if(n->d < ds[n->id]){
            ds[n->id] = n->d;
            for(auto e : graph[n->id].ns){
                if(ds[e.to] < INF){
                    continue;
                }
                node_s* next_n = new node_s {graph[e.to].id, ds[n->id] + e.w};
                que.push(next_n);
            }
        }
        delete n;
    }
    return ds;
}

int main(){
    cin.sync_with_stdio(false);
    cout.sync_with_stdio(false);
    int n;
    cin >> n;
    node graph[n];
    for(int i = 0; i < n; ++i){
        int id;
        int m;
        cin >> id >> m;
        auto vec = vector<edge>(m);
        int v, c;
        for(int j = 0; j < m; ++j){
            cin >> v >> c;
            vec[j] = edge {id, v, c};
        }
        graph[id] = node(id, vec);
    }
    auto ds = dijkstra(graph, n, 0);
    for(int i = 0; i < n; ++i){
        cout << i << ' ' << ds[i] << endl;
    }
}
