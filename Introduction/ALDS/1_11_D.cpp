#include <iostream>
#include <vector>
#include <stack>

using namespace std;

struct uft {
    uft (int s) : ps {new int[s]}, ds {new int[s]}, s {s} {
        for(int i = 0; i < s; ++i){
            ps[i] = i;
            ds[i] = 0;
        }
    };
    void unite(int x, int y){
        int px = parent(x);
        int py = parent(y);
        if(ds[px] < ds[py]){
            ps[px] = py;
        } else if(ds[px] > ds[py]){
            ps[py] = px;
        } else {
            ps[px] = py;
            ++ds[py];
        }
    };
    int parent(int p){
        return p == ps[p] ? p : ps[p] = parent(ps[p]);
    };
    bool same(int x, int y){
        return parent(x) == parent(y);
    };
    int* ps;
    int* ds;
    int s;
};

struct user {
    user() {};
    user(int i) : id {i}, fs {}, group {-1} {};
    int id;
    vector<int> fs;
    int group;
};

void add_friends(user *us, int x, int y){
    us[x].fs.push_back(y);
    us[y].fs.push_back(x);
}

void dfs(user* us, int id, int g){
    stack<int> ss {};
    ss.push(id);
    while(ss.size()){
        int p = ss.top();
        ss.pop();
        us[p].group = g;
        vector<int> fs = us[p].fs;
        for(auto x : fs){
            if(us[x].group == g){
                continue;
            }
            ss.push(x);
        }
    }
}

void make_group(user* us, int n){
    int g = 0;
    for(int i = 0; i < n; ++i){
        if(us[i].group < 0){
            dfs(us, i, g);
            ++g;
        }
    }
}

int main(){
    cin.sync_with_stdio(false);
    cout.sync_with_stdio(false);
    int n, m;
    cin >> n >> m;
    //user us[n];
    auto us = uft(n);
    /*for(int i = 0; i < n; ++i){
        us[i] = user(i);
    }*/
    for(int i = 0; i < m; ++i){
        int a, b;
        cin >> a >> b;
        us.unite(a, b);
    //    add_friends(us, a, b);
    }
    //make_group(us, n);
    int q;
    cin >> q;
    for(int i = 0; i < q; ++ i){
        int a, b;
        cin >> a >> b;
        //if(us[a].group == us[b].group){
        if(us.same(a, b)){
            cout << "yes" << endl;
        } else {
            cout << "no" << endl;
        }
    }
}
