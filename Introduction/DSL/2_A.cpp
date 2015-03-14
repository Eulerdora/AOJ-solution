#include <iostream>
#include <vector>
#include <cmath>

using namespace std;

int maxVal = pow(2, 31) - 1;
class RMQ {
public:
    RMQ(int n, int v) {
        int i = 1;
        while(i < n){
            i *= 2;
        }
        tree = vector<int>(i*2-1, v);
        st_idx = i-1;
        s = i*2-1;
    };
    void update(int x, int v){
        int idx = x + st_idx;
        tree[idx] = v;
        while(idx){
            int p = (idx-1)/2;
            int sb = idx%2 ? idx+1 : idx-1;
            tree[p] = min(tree[idx], tree[sb]);
            idx = p;
        }
    }
    int findMin(int l, int r){
        return findMin(l+st_idx, r+st_idx, maxVal);
    }
    void print(){
        for(int x : tree){
            cout << x << ' ';
        }
        cout << endl;
    }
private:
    vector<int> tree;
    int s;
    int st_idx;
    int findMin(int l, int r, int v){
        //cout << l  << ' ' << r << endl;
        if(l > r){
            return  v;
        }
        if(l == r){
            return min(v, tree[l]);
        }
        int minVal = v;
        if(l%2 == 0){
            minVal = min(minVal, tree[l]);
            l /= 2;
        } else {
            l = (l-1)/2;
        }
        if(r%2 == 1){
            minVal = min(minVal, tree[r]);
            r = (r-2)/2;
        } else {
            r = (r-1)/2;
        }
        return findMin(l, r, minVal);
    }
};

int main(){
    ios_base::sync_with_stdio(false);
    int n, q;
    cin >> n >> q;
    RMQ rmq = RMQ(n, maxVal);
    int com, x, y;
    for(int i = 0; i < q; ++i){
        cin >> com >> x >> y;
        if(com){
            int v = rmq.findMin(x, y);
            cout << v << endl;
        } else {
            rmq.update(x, y);
            //rmq.print();
        }
    }
}
