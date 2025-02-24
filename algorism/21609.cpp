// 블록은 검은색 블록, 무지개 블록, 일반 블록
// 일반 블록은 M가지 색상, M이하의 자연수로 표현, 검은색은 -1, 무지개는 0

// 블록 그룹에는 일반 블록이 적어도 하나 있어야함. 일반 블록 색은 다 같음. 대신 검은색 블록은 포함되면 안됨, 무지개는 상관x
// 그룹에 속한 블록의 개수는 2보다 크거나 같아야 함.
// 임의의 한 블록에서 그룹에 속한 인접한 칸으로 이동해서 그룹에 속한 다른 모든 칸으로 이동할 수 있어야 함.
// 그룹의 기준 블록은, 무지개 블록을 제외하고 행의 번호가 가장 작은 블록, 여러개면 열으 ㅣ번호가 가장 작은 블록

// 1. 크기가 가장 큰 블록 그룹을 찾고 그러한 블록 그룹이 여러 개라면 무지개 블록의 수가 가장 많은 블록 그룹, 그것도 여러개라면 기준 블록의 행이 가장 큰 것, 그것도 여러 개면 열이 가장 큰 것
// 2. 그룹의 모든 블록 제거. 블록의 수를 B라고 했을때, B^2점을 획득.
// 3. 격자에 중력이 작용
// 4. 격자가 90도 반시계 방향 회전
// 5. 다시 격자에 중력이 작용


#include <stdio.h>
#include <iostream>
#include <vector>
#include <queue>
using namespace std;

const int dx[] = {-1,0,1,0};
const int dy[] = {0,-1,0,1};

int N, M;
int board[20][20];

int calcPoint() {
    int point = 0;
    vector<int> maxArea;
    int maxRainbow = 0;
    for (int color = 1; color <= M; color++){
        bool visited[20][20] = {false, };
        for (int x = 0; x < N; x++){
            for (int y = 0; y < N; y++){
                if(visited[x][y] == false && board[x][y] == color){
                    queue<int> q;
                    vector<int> vec;
                    int rainbow = 0;

                    q.push(x * 100 + y);
                    vec.push_back(x * 100 + y);
                    visited[x][y] = true;

                    while (!q.empty()) {
                        int cx = q.front() / 100;
                        int cy = q.front() % 100;
                        q.pop();

                        for (int d = 0; d < 4; d++){
                            int nx = cx + dx[d];
                            int ny = cy + dy[d];

                            if (nx >= 0 && nx <N && ny >= 0 && ny < N){
                                if(visited[nx][ny] == false && (board[nx][ny] == color || board[nx][ny] == 0)){
                                    q.push(nx * 100 + ny);
                                    vec.push_back(nx * 100 + ny);
                                    visited[nx][ny] = true;
                                    if (board[nx][ny] == 0){
                                        rainbow++;
                                    }
                                }
                            }
                        }
                        if (maxArea.size() < vec.size() ||
                            (maxArea.size() == vec.size() && maxRainbow < rainbow)|| 
                            (maxArea.size() == vec.size() && maxRainbow == rainbow && maxArea[0] < vec[0])){
                            maxArea.resize(vec.size());
                            copy(vec.begin(), vec.end(), maxArea.begin());
                            maxRainbow = rainbow;
                        }
                    }
                }
            }
        }
    }
    if (maxArea.size() >= 2){
        point = maxArea.size() * maxArea.size();
        for (int i = 0; i < maxArea.size(); i++){
            int x = maxArea[i] / 100;
            int y = maxArea[i] % 100;
            board[x][y] = -2;
        }
    }
    return point;
}

void down() {
    for (int y = 0; y < N; y++){
        int blank = 0;
        for (int x = N - 1; x >= 0; x--){
            if (board[x][y] == -2){
                blank++;
            }
            else if (board[x][y] == -1) {
                blank = 0;
            }
            else {
                if(blank != 0) {
                    board[x + blank][y] = board[x][y];
                    board[x][y] = -2;
                }
            }
        }
    }
}
void rotate() {
    int back[20][20];

    for (int x = 0; x < N; x++){
        for (int y = 0; y < N; y++){
            back[N - 1 - y][x] = board[x][y];
        }
    }

    for (int x = 0; x < N; x++){
        for (int y = 0; y < N; y++){
            board[x][y] = back[x][y];
        }
    }
}

int solve() {
    int point = 0;
    int curPoint = 0;

    do {
        curPoint = calcPoint();
        point += curPoint;
        down();
        rotate();
        down();
    } while (curPoint !=0);

    return point;
}



int main(){

    scanf("%d %d", &N, &M);
    for (int x = 0; x < N; x++){
        for (int y = 0; y < N; y++){
            scanf("%d", &board[x][y]);
        }
    }
    int ret = solve();
    printf("%d\n", ret);
    return 0;
}