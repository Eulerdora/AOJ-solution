#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;
struct edge {
    edge() {};
    edge(int s, int e, int d) : start {s}, end {e}, d {d} {};
    int start;
    int end;
    int d;
};

void dfs(vector<vector<int>>& graph, bool* used, int id, int n){
    used[id] = true;
    for(int i = 0; i < n; ++i){
        if(graph[id][i] == -1 || used[i]){
            continue;
        }
        dfs(graph, used, i, n);
    }
}

bool is_connected(vector<vector<int>>& graph){
    int n = graph.size();
    bool used[n];
    for(int i = 0; i < n; ++i){
        used[i] = false;
    }
    dfs(graph, used, 0, n);
    for(int i = 0; i < n; ++i){
        if(!used[i]){
            return false;
        }
    }
    return true;
}

void delete_edges(vector<vector<int>>& graph){
    int edges_num = 0;
    vector<edge> vec {};
    int n = graph.size();
    for(int i = 0; i < n; ++i){
        for(int j = i+1; j < n; ++j){
            if(graph[i][j] != -1){
                ++edges_num;
                vec.push_back(edge(i, j, graph[i][j]));
            }
        }
    }
    sort(vec.begin(), vec.end(), [](edge x, edge y){
            return y.d < x.d;
         });

    for(auto it = vec.begin(); it != vec.end(); ++it){
        edge e = *it;
        graph[e.start][e.end] = -1;
        graph[e.end][e.start] = -1;
        if(is_connected(graph)){
            --edges_num;
            if(edges_num == n-1){
                return;
            }
        } else {
            graph[e.start][e.end] = e.d;
            graph[e.end][e.start] = e.d;
        }
    }
}

vector<vector<int>> gen_spanning_tree(vector<vector<int>>& graph){
    vector<vector<int>> tree {graph};
    delete_edges(tree);
    return tree;
}

int calc_weight(vector<vector<int>> graph){
    int sum = 0;
    int n = graph.size();
    for(int i = 0; i < n; ++i){
        for(int j = i+1; j < n; ++j){
            if(graph[i][j] == -1){
                continue;
            }
            sum += graph[i][j];
        }
    }
    return sum;
}

int main(){
    int n;
    cin >> n;
    vector<vector<int>> graph {n, vector<int>(n, 0)};
    for(int i = 0; i < n; ++i){
        for(int j = 0; j < n; ++j){
            cin >> graph[i][j];
        }
    }
    auto tree = gen_spanning_tree(graph);

    cout << calc_weight(tree) << endl;
}
