#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;
class Point {
public:
    Point(){};
    Point(int i, int x, int y) : id {i}, x {x}, y {y} {};
    int id;
    int x;
    int y;
};

class TwoDTree {
public:
    TwoDTree(){};
    TwoDTree(Point* p, TwoDTree* l, TwoDTree* r) : root {p}, left {l}, right {r} {};
    TwoDTree(vector<Point>& ps) {
        auto tree = const2DTree(ps.begin(), ps.end(), 0);
        root = tree->root;
        left = tree->left;
        right = tree->right;
    };
    typedef vector<Point>::iterator pIter;

    TwoDTree* const2DTree(pIter a, pIter b, int d){
        if(a >= b){
            return nullptr;
        }
        if(d%2){
            sort(a, b, [](Point p, Point q){ return p.y < q.y; });
        } else {
            sort(a, b, [](Point p, Point q){ return p.x < q.x; });
        }
        pIter mid = a + (b-a)/2;
        auto l = const2DTree(a, mid, d+1);
        auto r = const2DTree(mid+1, b, d+1);
        return new TwoDTree(&(*mid), l, r);
    };
    vector<Point> find(int x1, int x2, int y1, int y2){
        auto ps = new vector<Point>();
        find(x1, x2, y1, y2, 0, *ps);
        return *ps;
    };
    Point* root;
    TwoDTree* left;
    TwoDTree* right;
private:
    void find(int x1, int x2, int y1, int y2, int d, vector<Point>& vec){
        if(!root){
            return;
        }
        int rx = root->x;
        int ry = root->y;
        if(x1 <= rx && rx <= x2 && y1 <= ry && ry <= y2){
            vec.push_back(*root);
        }

        if(left){
            if(d%2 == 0 && rx >= x1){
                left->find(x1, x2, y1, y2, d+1, vec);
            } else if(d%2 == 1 && ry >= y1){
                left->find(x1, x2, y1, y2, d+1, vec);
            }
        }
        if(right){
            if(d%2 == 0 && rx <= x2){
                right->find(x1, x2, y1, y2, d+1, vec);
            } else if(d%2 == 1 && ry <= y2){
                right->find(x1, x2, y1, y2, d+1, vec);
            }
        }
    }
};

int main(){
    ios_base::sync_with_stdio(false);
    int n;
    cin >> n;
    auto ps = vector<Point>();
    int x, y;
    for(int i = 0; i < n; ++i){
        cin >> x >> y;
        ps.push_back(Point(i, x, y));
    }
    auto kdTree = TwoDTree(ps);
    int q;
    cin >> q;
    int sx, tx, sy, ty;
    for(int i = 0; i < q; ++i){
        cin >> sx >> tx >> sy >> ty;
        auto vs = kdTree.find(sx, tx, sy, ty);
        sort(vs.begin(), vs.end(), [](Point a, Point b){
                return a.id < b.id;
             });
        for(auto x : vs){
            printf("%d\n", x.id);
        }
        printf("\n");
    }
}
