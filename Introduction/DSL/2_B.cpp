#include <iostream>
#include <vector>

using namespace std;
class BIT {
public:
    BIT(int n) : vec {vector<int>(n, 0)} {};
    int sum(int l, int r){
        return sum(r) - sum(l-1);
    }
    void add(int i, int v){
        int idx = i;
        int vs = vec.size();
        while(idx <= vs){
            vec[idx-1] += v;
            idx += idx&(-idx);
        }
    }
    void print(){
        for(auto x : vec){
            cout << x << ' ';
        }
        cout << endl;
    }
private:
    vector<int> vec;
    int sum(int x){
        //cout << "x = " << x << ", ";
        if(!x){
         //   cout << "sum = " << 0 << endl;
            return 0;
        }
        int s = 0;
        while(x){
            s += vec[x-1];
            x = x&(x-1);
        }
        //cout << "sum = " << s << endl;
        return s;
    }
};

int main(){
    ios_base::sync_with_stdio(false);
    int n, q;
    cin >> n >> q;
    auto bit = BIT(n);
    //bit.print();
    int com, x, y;
    for(int i = 0; i < q; ++i){
        cin >> com >> x >> y;
        if(com){
            cout << bit.sum(x, y) << endl;
        } else {
            bit.add(x, y);
            //bit.print();
        }
    }
}
