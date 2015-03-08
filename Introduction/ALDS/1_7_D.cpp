#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;
void postorder(vector<int>& pre, vector<int>& in, vector<int>& ret)
{
    if(in.size() <= 1)
    {
        for(auto it = in.begin(); it != in.end(); ++it)
        {
            ret.push_back(*it);
        }
        return;
    }
    int root = pre[0];
    int ln = find(in.begin(), in.end(), root) - in.begin();

    vector<int> pre_left {};
    pre_left.insert(pre_left.begin(), pre.begin()+1, pre.begin()+ln+1);
    vector<int>in_left {};
    in_left.insert(in_left.begin(), in.begin(), in.begin()+ln);

    vector<int> pre_right {};
    pre_right.insert(pre_right.begin(), pre.begin()+ln+1, pre.end());
    vector<int> in_right {};
    in_right.insert(in_right.begin(), in.begin()+ln+1, in.end());

    vector<int> pre_mid {root};
    vector<int> in_mid {root};

    postorder(pre_left, in_left, ret);
    postorder(pre_right, in_right, ret);
    postorder(pre_mid, in_mid, ret);
}
int main()
{
    int n;
    cin >> n;
    vector<int> pre {};
    vector<int> in {};
    for(int i = 0; i < n; ++i)
    {
        int temp;
        cin >> temp;
        pre.push_back(temp);
    }
    for(int i = 0; i < n; ++i)
    {
        int temp;
        cin >> temp;
        in.push_back(temp);
    }
    vector<int> post {};
    postorder(pre, in, post);
    for(auto it = post.begin(); it != post.end(); ++it)
    {
        if(it == post.begin())
        {
            cout << *it;
        }
        else
        {
            cout << " " << *it;
        }
    }
    cout << endl;
}
