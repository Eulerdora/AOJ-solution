#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;
bool is_valid(vector<int>& board){
    auto cross = vector<bool>(16, false);
    auto diagon = vector<bool>(16, false);
    for(auto it = board.begin(); it != board.end(); ++it){
        int idx = it - board.begin();
        int c = *it - idx + 8;
        int d = 16 - *it - idx;
        if(cross[c] || diagon[d]){
            return false;
        }
        cross[c] = true;
        diagon[d] = true;
    }
    return true;
}

int main(){
    int n;
    cin >> n;
    auto board = vector<int>(8, -1);
    for(int i = 0; i < n; ++i){
        int x, y;
        cin >> x >> y;
        board[x] = y;
    }
    vector<int> xs {};
    vector<int> ys {};
    for(int i = 0; i < 8; ++i){
        if(board[i] == -1){
            xs.push_back(i);
        }
        bool flag = false;
        for(int j = 0; j < 8; ++j){
            if(board[j] == i){
                flag = true;
                break;
            }
        }
        if(!flag){
            ys.push_back(i);
        }
    }
    int s = xs.size();
    while(1){
        for(int i = 0; i < s; ++i){
            board[xs[i]] = ys[i];
        }
        if(is_valid(board)){
            break;
        }
        if(!next_permutation(ys.begin(), ys.end())){
            break;
        }
    }
    for(int i = 0; i < 8; ++i){
        for(int j = 0; j < 8; ++j){
            cout << (board[i] == j ? 'Q' : '.');
        }
        cout << endl;
    }
}
