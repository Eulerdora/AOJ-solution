#include <iostream>
#include <vector>
#include <cmath>

using namespace std;
struct coord
{
    double x;
    double y;
};

coord rotate(coord p)
{
    double nx = p.x/2 - p.y*sqrt(3)/2;
    double ny = p.x*sqrt(3)/2 + p.y/2;
    return coord {nx, ny};
}

vector<coord> koch(coord a, coord b)
{
    auto vec = vector<coord>();
    coord p1 = coord {(a.x*2+b.x)/3, (a.y*2+b.y)/3};
    coord p2 = coord {(a.x+2*b.x)/3, (a.y+2*b.y)/3};
    coord v = coord {p2.x-p1.x, p2.y-p1.y};
    coord nv = rotate(v);
    coord p3 = coord {p1.x+nv.x, p1.y+nv.y};
    vec.push_back(a);
    vec.push_back(p1);
    vec.push_back(p3);
    vec.push_back(p2);
    vec.push_back(b);
    return vec;
}

vector<coord> koch(vector<coord>& vec, int d)
{
    if(!d)
    {
        return vec;
    }
    auto ret = vector<coord>();
    for(auto it = vec.begin(); it != vec.end()-1; ++it)
    {
        auto vs = koch(*it, *(it+1));
        if(it == vec.begin())
        {
            ret.insert(ret.end(), vs.begin(), vs.end());
        }
        else
        {
            ret.insert(ret.end(), vs.begin()+1, vs.end());
        }
    }
    return koch(ret, d-1);
}

int main()
{
    int n;
    cin >> n;
    vector<coord> vs {coord {0.0, 0.0}, coord {100.0, 0.0}};
    auto vec = koch(vs, n);
    for(auto it = vec.begin(); it != vec.end(); ++it)
    {
        printf("%f %f\n", it->x, it->y);
    }
}
