#include <iostream>
#include <vector>
#include <queue>
#include <cmath>

using namespace std;
constexpr int board_len = 4;
constexpr int cell_num = board_len*board_len;
constexpr int depth_limit = 46;

struct state {
    state() : board {nullptr}, zero {}, num {}, correct {} {};
    state(vector<int>* vec, int z, int c, int n) : board {vec}, zero {z}, num {n}, correct {c} {};
    vector<int>* board;
    int zero;
    int num;
    int correct;
    void print(){
        cout << "board" << endl;
        for(int i = 0; i < cell_num; ++i){
            cout << (*board)[i] << ' ';
            if(i%board_len == (board_len-1)){
                cout << endl;
            }
        }
        cout << "zero = " << zero << ", num = " << num << ", correct = " << correct << endl;
    }
};

bool correct_pos(vector<int>& vec, int id){
    return (id+1)%cell_num == vec[id];
}

int calc_dist(int pos, int target){
    int px = pos/board_len;
    int py = pos%board_len;
    int tx = (target-1)/board_len;
    int ty = (target-1)%board_len;
    return abs(tx-px) + abs(ty-py);
}

int min_cost(vector<int>& vec){
    int sum = 0;
    for(int i = 0; i < cell_num; ++i){
        if(vec[i]){
            sum += calc_dist(i, vec[i]);
        }
    }
    return sum;
}

state dfs_arg(state& now, int pos){
    if(pos >= 0 && pos < cell_num){
        //cout << "dfs_arg called, pos = " << pos << endl;
        //now.print();
        int nc = now.correct;
        if(correct_pos(*now.board, pos)){
            --nc;
        }
        if(correct_pos(*now.board, now.zero)){
            --nc;
        }
        swap((*now.board)[pos], (*now.board)[now.zero]);
        if(correct_pos(*now.board, pos)){
            ++nc;
        }
        if(correct_pos(*now.board, now.zero)){
            ++nc;
        }
        state next_st = state(now.board, pos, nc, now.num+1);
        return next_st;
    } else {
        return state();
    }
}

int iterative_deepening(state& st, int limit){
    if(st.correct == cell_num){
        return st.num;
    }
    int cost = st.num + min_cost(*st.board);
    //st.print();
    //cout << "cost = " << cost << endl;
    if(cost > limit){
        return 1000000000;
    }
    int up = st.zero - board_len;
    int down = st.zero + board_len;
    int left = st.zero%board_len ? st.zero - 1 : -1;
    int right = st.zero%board_len != (board_len-1) ? st.zero + 1 : -1;

    int ret = 1000000000;
    state up_st = dfs_arg(st, up);
    if(up_st.board){
    //    cout << "before up" << endl;
    //    cout << "exchanged " << st.zero << " and " << up << endl;
    //    up_st.print();
        ret = min(ret, iterative_deepening(up_st, limit));
        vector<int>* vec = up_st.board;
        swap(vec->at(st.zero), vec->at(up));
 //       cout << "after up" << endl;
 //       cout << "reexchanged " << st.zero << " and " << up << endl;
 //       up_st.print();
    }
    state down_st = dfs_arg(st, down);
    if(down_st.board){
  //      cout << "before down" << endl;
  //      cout << "exchanged " << st.zero << " and " << down << endl;
  //      down_st.print();
        ret = min(ret, iterative_deepening(down_st, limit));
        vector<int>* vec = down_st.board;
        swap(vec->at(st.zero), vec->at(down));
  //      cout << "after down" << endl;
  //      cout << "reexchanged " << st.zero << " and " << down << endl;
  //      down_st.print();
    }
    state left_st = dfs_arg(st, left);
    if(left_st.board){
  //      cout << "left" << endl;
  //      cout << "exchanged " << st.zero << " and " << left << endl;
 //       left_st.print();
        ret = min(ret, iterative_deepening(left_st, limit));
        vector<int>* vec = left_st.board;
        swap(vec->at(st.zero), vec->at(left));
   //     cout << "after left" << endl;
   //     cout << "reexchanged " << st.zero << " and " << left << endl;
   //     left_st.print();
    }
    state right_st = dfs_arg(st, right);
    if(right_st.board){
  //      cout << "right" << endl;
  //      cout << "exchanged " << st.zero << " and " << right << endl;
  //      right_st.print();
        ret = min(ret, iterative_deepening(right_st, limit));
        vector<int>* vec = right_st.board;
        swap(vec->at(st.zero), vec->at(right));
   //     cout << "after right" << endl;
   //     cout << "reexchanged " << st.zero << " and " << right << endl;
   //     right_st.print();
    }
    return ret;
}

int find_minimum(vector<int>& vec){
    int zero = 0;
    int correct = 0;
    for(auto it = vec.begin(); it != vec.end(); ++it){
        int i = it - vec.begin();
        if(*it == 0){
            zero = i;
        }
        if(correct_pos(vec, i)){
            ++correct;
        }
    }
    vector<int>* board = new vector<int>(vec);
    state st = state(board, zero, correct, 0);
    for(int i = 0; i < depth_limit; ++i){
        int ret = iterative_deepening(st, 46);
        //cout << "depth " << i << ", ret = " << ret << endl;
        if(ret < 46){
            return ret;
        }
    }
}

int main(){
    vector<int> board {};
    for(int i = 0; i < 16; ++i){
        int v;
        cin >> v;
        board.push_back(v);
    }
    cout << find_minimum(board) << endl;
}
