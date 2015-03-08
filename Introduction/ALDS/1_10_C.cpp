#include <iostream>
#include <vector>
#include <array>

using namespace std;

long minimum_product(const vector<int>& vec, int p, int q, vector<vector<int>>& dp)
{
    if(q-p <= 1)
    {
        return 0;
    }
    if(dp[p][q])
    {
        return dp[p][q];
    }
    int ret = 2000000000;
    for(int i = p+1; i < q; ++i)
    {
        int product = vec[p]*vec[q]*vec[i] + minimum_product(vec, p, i, dp)
                      + minimum_product(vec, i, q, dp);
        if(product < ret)
        {
            ret = product;
        }
    }
    return dp[p][q] = ret;
}

int main()
{
    vector<int> vec {};
    int n;
    cin >> n;
    for(int i = 0; i < n; ++i)
    {
        int a, b;
        cin >>  a >> b;
        if(i == 0)
        {
            vec.push_back(a);
        }
        vec.push_back(b);
    }
    vector<vector<int>> dp {n+1, vector<int>(n+1, 0)};
    cout << minimum_product(vec, 0, n, dp) << endl;
}
