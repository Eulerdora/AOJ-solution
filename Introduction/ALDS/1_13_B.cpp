#include <iostream>
#include <vector>
#include <queue>
#include <set>

using namespace std;
struct state {
    state(vector<int> vec, int z, int c, int n) : board {vec}, zero {z}, correct {c}, num {n} {};
    vector<int> board;
    int zero;
    int correct;
    int num;
    void print(){
        cout << "board" << endl;
        for(int i = 0; i < 9; ++i){
            cout << board[i] << ' ';
            if(i%3 == 2){
                cout << endl;
            }
        }
        cout << "correct = " << correct << ", zero = " << zero << ", n = " << num << endl;
    }
};

multiset<vector<int>> memo {};

bool correct_pos(vector<int>& vec, int id){
    return (id+1)%9 == vec[id];
}

void push_queue(queue<state>& states, state now, int pos){
    if(pos >= 0 && pos < 9){
        int nc = now.correct;
        if(correct_pos(now.board, pos)){
            --nc;
        }
        if(correct_pos(now.board, now.zero)){
            --nc;
        }
        swap(now.board[pos], now.board[now.zero]);
        if(correct_pos(now.board, pos)){
            ++nc;
        }
        if(correct_pos(now.board, now.zero)){
            ++nc;
        }
        bool pushed = memo.find(now.board) != memo.end();
        if(pushed){
        //    cout << "already searched, pos = " << pos << endl;
            return;
        } else {
            memo.insert(now.board);
        }
        state next_st = state(vector<int>(now.board), pos, nc, now.num+1);
        //cout << "pushing" << endl;
        //next_st.print();
        states.push(next_st);
        swap(now.board[pos], now.board[now.zero]);
    }
}

int bfs(queue<state>& states){
    int ret = 0;
    while(states.size()){
        state s = states.front();
        states.pop();
        if(s.correct == 9){
            ret = s.num;
            break;
        }
        int up = s.zero - 3;
        int down = s.zero + 3;
        int left = s.zero%3 ? s.zero - 1 : -1;
        int right = s.zero%3 != 2 ? s.zero + 1 : -1;
        //cout << up << " " << down << " " << left << " " << right << endl;
        push_queue(states, s, up);
        push_queue(states, s, down);
        push_queue(states, s, left);
        push_queue(states, s, right);
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
    auto st = queue<state>();
    st.push(state(vec, zero, correct, 0));
    return bfs(st);
}

int main(){
    vector<int> board {};
    for(int i = 0; i < 9; ++i){
        int v;
        cin >> v;
        board.push_back(v);
    }
    cout << find_minimum(board) << endl;
}
