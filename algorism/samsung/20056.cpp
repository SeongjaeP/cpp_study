// N x N인 격자에 파이어볼 M개를 발사
// r,c,m,d,s
// 이동하는 중에 같은 칸에 여러 개의 파이어볼 가능
// 이동이 끝난 뒤 2개 이상의 파이어볼이 있는 칸에는 무슨 일이 일어남
// 1. 하나로 합쳐짐
// 2. 4개로 나누어짐
// 3. 나눠지면 질량 속력 방향이 있어야할거아녀
//  1. 질량은 합쳐진 파이어볼 질량의 합 / 5
//  2. 속력은 (합쳐진 파이어볼 속력 합)/ (합쳐진 파이어볼의 개수)
//  3. 합쳐지는 파이어볼의 방향이 모두 홀수이거나 모두 짝수이면, 방향은 0, 2, 4, 6 그렇지 않으면 1, 3, 5, 7 
// 4. 질량이 0인 파이어볼은 소멸됨

// 그 칸에 몇 개 있는지 세는 것도 필요할 거 같음.


#include <iostream>
#include <vector>
using namespace std;


struct FIREBALL {
    int x, y;
    int m, s, d;
};

// 방향에 따른 move
const int dx[8] = {-1, -1, 0, 1, 1, 1, 0, -1};
const int dy[8] = {0, 1, 1, 1, 0, -1, -1, -1};



int N,M,K;
vector<int> map[50][50];
vector<FIREBALL> ball;

void move() {
    vector<int> new_map[50][50];
    for (int i = 0; i < ball.size(); i++){
        int dir = ball[i].d;
        int speed = ball[i].s;
        int nx = ((ball[i].x + (dx[dir] * speed)) % N + N) % N; // 범위를 벗어나는 부분을 처리해줭함. 
        int ny = ((ball[i].y + (dy[dir] * speed)) % N + N) % N;
        new_map[nx][ny].push_back(i);
        ball[i].x = nx;
        ball[i].y = ny;
    }

    for (int x = 0; x < N; x++){
        for (int y = 0; y < N; y++){
            map[x][y] = new_map[x][y];
        }
    }
}

void sum(){
    vector<FIREBALL> new_ball;
    for (int x = 0; x < N; x++){
        for (int y = 0; y < N; y++){
            if (map[x][y].size() == 0){
                continue;
            }
            if (map[x][y].size() == 1){
                int index = map[x][y][0];
                new_ball.push_back(ball[index]);
                continue;
            }
            int sum_m = 0, sum_s = 0;
            // 일단 디폴트를 true로 해놓고 하나라도 어긋나면 false로 바꾸게 끔 설게하기.
            bool odd = true, even = true;

            for (int i = 0; i < map[x][y].size(); i++){
                int index = map[x][y][i];
                sum_m += ball[index].m;
                sum_s += ball[index].s;
                
                if (ball[index].d % 2 == 0){
                    odd = false; 
                }
                else {
                    even = false;
                }
            }

            if (sum_m / 5  == 0) {
                continue;
            }
            int cur_m = sum_m / 5;
            int cur_s = sum_s / map[x][y].size();

            for (int i = 0; i < 4; i++){
                if(odd || even) {
                    new_ball.push_back({x, y, cur_m ,cur_s, i * 2});
                }
                else{
                    new_ball.push_back({x, y, cur_m, cur_s, i * 2 + 1});
                }
            }

        }
    }
    ball = new_ball;
}


int solve(){
    while(K--){
        move();
        sum();
    }

    int ret = 0;
    for (int i = 0; i < ball.size(); i++){
        ret += ball[i].m;
    }
    return ret;
}


int main(){
    cin >> N >> M >> K;

    for (int i = 0; i < M; i++){
        int x, y, m, s, d;
        cin >> x >> y >> m >> s >> d;
        x--, y--;
        ball.push_back({x, y, m, s, d});
        map[x][y].push_back(i);
    }

    int ret = solve();
    cout << ret << endl;
    return 0;
    
}