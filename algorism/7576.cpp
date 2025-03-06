#include <iostream>
#include <queue>
#include <cstring>

using namespace std;

int M, N;
int board[1000][1000];
int days[1000][1000];
queue<pair<int ,int>> q;

const int dx[4] = {1, -1, 0, 0};
const int dy[4] = {0, 0, 1, -1};


void input(){
    cin >> M >> N;

    bool all_ripe = true; //  전부 0이면 계산할 필요가 없음.
    memset(days, -1, sizeof(days)); // 왜 추가?

    for (int i = 0; i < N; i++){
        for (int j = 0; j < M; j++){
            cin >> board[i][j];

            if (board[i][j] == 1){
                q.push({i, j});
                days[i][j] = 0;
            }
            else if (board[i][j] == 0){
                all_ripe = false;
            }
        }
    }
    if (all_ripe){
        cout << "0\n";
        exit(0);
        }
    
}

void bfs(){
    while(!q.empty()){
        int x = q.front().first;
        int y = q.front().second;
        q.pop();

        for (int i = 0; i < 4; i++){
            int nx = x + dx[i];
            int ny = y + dy[i];

            if (nx >= 0 && nx < N && ny >= 0 && ny < M) {
                if (board[nx][ny] == 0){
                    board[nx][ny] = 1;
                    days[nx][ny] = days[x][y] + 1;
                    q.push({nx, ny});
                }
            }
        }
    }
}

void output() {
    int max_days = 0;
    bool unripe_exists = false;

    // 0 이 있다 그러면 -1

    for (int i = 0; i < N; i++){
        for (int j = 0; j < M; j++){
            if (board[i][j] == 0){
                unripe_exists = true; // 안 익은게 있는거임.
            }
            max_days = max(max_days, days[i][j]);
        }
    }
    if (unripe_exists){
        cout << "-1\n";
    }
    else{
        cout << max_days << endl;
    }

}


int main() {
    input();  
    bfs();   
    output(); 
}