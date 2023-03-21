#include<iostream>
#include<vector>
#include<queue>
#include<cstring>
#include<algorithm>
using namespace std;

// 승객수만큼 while문 반복
// 한 승객을 목적지로 성공적으로 이동시키면, 소모한 연료 양의 두배가 충전
// 이동하는 동안 연료가 바닥나면 이동실패
// 목적지로 이동시킨 동시에 연료 바닥나는 경우는 괜찮음

struct yx {
    int y;
    int x;
};

int MAP[21][21];
int visited[21][21] = { 0 };
int N, M, first_fuel;
int start_y, start_x;

int ydir[4] = { -1,1,0,0 };
int xdir[4] = { 0,0,-1,1 };

vector<yx>guest_vect;
vector<yx>dest_vect;

void bfs(int y, int x) {

    while (M--) {

        // 거리가 가장 가까운 승객 찾아서 이동하기
        memset(visited, 0, sizeof(visited));

        queue<yx>q;
        q.push({ y,x });
        visited[y][x] = 1;

        while (!q.empty()) {
            yx now = q.front();
            q.pop();

            for (int i = 0; i < 4; i++) {
                int ny = now.y + ydir[i];
                int nx = now.x + xdir[i];

                if (ny<1 || nx<1 || ny>N || nx>N)continue;
                if (MAP[ny][nx] == 1)continue;
                if (visited[ny][nx] > 0)continue;

                visited[ny][nx] = visited[now.y][now.x] + 1;

                q.push({ ny,nx });

            }
        }

        int min_dist = 9999; //최소거리 찾기
        int move_y = 0; // 이동할 좌표 구하기
        int move_x = 0;
        int g_index = 0; // 데러러갈 손님의 index

        int gvect_size = guest_vect.size();
        for (int i = 0; i < gvect_size; i++) {

            // 이동거리가 최소인 승객 찾기
            if (min_dist > visited[guest_vect[i].y][guest_vect[i].x]) {
                min_dist = visited[guest_vect[i].y][guest_vect[i].x];
                move_y = guest_vect[i].y;
                move_x = guest_vect[i].x;
                g_index = i;
            } //만약 이동거리가 동일한 경우에
            else if (min_dist == visited[guest_vect[i].y][guest_vect[i].x]) {
                // 행 번호가 가장 작은 승객
                if (move_y > guest_vect[i].y) {
                    move_y = guest_vect[i].y;
                    move_x = guest_vect[i].x;
                    g_index = i;
                } // 행 번호도 같으면 열 번호가 가장 작은 승객
                else if (move_y == guest_vect[i].y && move_x > guest_vect[i].x) {
                    move_y = guest_vect[i].y;
                    move_x = guest_vect[i].x;
                    g_index = i;
                }

            }
        }
        // 이동한 승객에 대한 정보 vect에서 지워주기
        guest_vect.erase(guest_vect.begin() + g_index);
        first_fuel = first_fuel - (visited[move_y][move_x] - 1); // 연료 계산

        // 만약 승객한테 도착하지 못했거나 연료가 바닥나면 -1로 해주고 끝내기
        if (visited[move_y][move_x] == 0 || first_fuel <= 0) {
            first_fuel = -1;
            break;
        }


        // 승객을 태우고 그 승객의 목적지에 해당하는 곳 까지 이동
        memset(visited, 0, sizeof(visited));

        queue<yx>q1;
        q1.push({ move_y,move_x });
        visited[move_y][move_x] = 1;

        while (!q1.empty()) {
            yx now = q1.front();
            q1.pop();

            for (int i = 0; i < 4; i++) {
                int ny = now.y + ydir[i];
                int nx = now.x + xdir[i];

                if (ny<1 || nx<1 || ny>N || nx>N)continue;
                if (MAP[ny][nx] == 1)continue;
                if (visited[ny][nx] > 0)continue;

                visited[ny][nx] = visited[now.y][now.x] + 1;

                q1.push({ ny,nx });

            }
        }

        // 승객 index를 이용해서 목적지 좌표 
        int dest_y = dest_vect[g_index].y;
        int dest_x = dest_vect[g_index].x;

        // 이동한 목적지에 대한 정보도 지워주기
        dest_vect.erase(dest_vect.begin() + g_index);
        first_fuel = first_fuel - (visited[dest_y][dest_x] - 1);

        //목적지에 이동하지 못했거나 목적지에 도착했을 때 연료가 0보다 작아지면 나가기
        if (visited[dest_y][dest_x] == 0 || first_fuel < 0) {
            first_fuel = -1;
            break;
        }
        // 만약 실패가 아니라면 승객을 태우고 목적지로 이동한 만큼의 2배 연료 채워주기
        first_fuel = first_fuel + (visited[dest_y][dest_x] - 1) * 2;

        // 다음 턴을 위해서 시작 좌표 변경
        y = dest_y;
        x = dest_x;
    }
}


int main() {
    // N, M, 초기 연료의 양
    // N개의 줄에 걸쳐 지도
    // 백준이 운전을 시작하는 칸의 행,열번호 -> 운전을 시작하는 칸은 빈칸
    // M개의 줄에 걸쳐 승객의 출발지의 행, 열번호/ 목적지의 행, 열번호

    ios::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);

    cin >> N >> M >> first_fuel;

    for (int i = 1; i <= N; ++i) {
        for (int j = 1; j <= N; ++j) {
            cin >> MAP[i][j];
        }
    }

    cin >> start_y >> start_x;

    for (int i = 0; i < M; ++i) {
        int g_y, g_x, d_y, d_x;
        cin >> g_y >> g_x >> d_y >> d_x;
        guest_vect.push_back({ g_y,g_x }); // 손님 좌표 벡터에 담기
        dest_vect.push_back({ d_y,d_x }); // 목적지 좌표 벡터에 담기
    }

    bfs(start_y, start_x);

    cout << first_fuel;

    return 0;
}