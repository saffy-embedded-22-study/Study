#include <iostream>
#include <vector>
#include <queue>

using namespace std;

char MAP[11][11];
int N, M;

struct marble {
    int y;
    int x;
    int cnt;
    int dest;
};

int ydir[4] = { -1,1,0,0 };
int xdir[4] = { 0,0,-1,1 };

queue<marble>red_m; // 빨간구슬 정보
queue<marble>blue_m; // 파란구슬 정보

marble move_m(marble,int); // 구슬 한방향으로 이동시키기
int bfs();


int main() {

    ios::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);

    cin >> N >> M;

    for (int i = 0; i < N; i++) {
        for (int j = 0; j < M; j++) {
            cin >> MAP[i][j];
            if (MAP[i][j] == 'R') {
                red_m.push({ i,j,0,0 });
            }
            else if (MAP[i][j] == 'B') {
                blue_m.push({ i,j,0,0 });
            }
        }
    }

    int ans = bfs();

    cout << ans << '\n';

    return 0;
}


int bfs() {
    // 10번 이하로 움직이는 경우에만
    while (red_m.front().cnt < 10 || blue_m.front().cnt < 10) { 
        marble r_now = red_m.front();
        marble b_now = blue_m.front();

        r_now.dest = 0; b_now.dest = 0; //거리값은 항상 초기화해주기
        red_m.pop(); blue_m.pop();

        for (int i = 0; i < 4; i++) {
            marble r_next = move_m(r_now, i); // 한방향으로 이동시켜보기
            marble b_next = move_m(b_now, i);

            r_next.cnt = r_now.cnt + 1; // 한 번 움직였으니까 cnt값 증가
            b_next.cnt = b_now.cnt + 1;

            int bny = b_next.y, bnx = b_next.x; // 각 구슬의 새로운 좌표
            int rny = r_next.y, rnx = r_next.x;

            if (MAP[bny][bnx] == 'O')continue; // 파란구슬이 빠지면 넘어가기
            if (MAP[rny][rnx] == 'O')return r_next.cnt; // 빨간구슬이 빠지면 값 리턴
            if (bny == rny && bnx == rnx) { // 만약 파란구슬이랑 빨간구슬이 겹치는 경우
                // 파란구슬과 빨간구슬의 이동한 거리 계산해서 더 큰 쪽을 한칸 전으로 움직여주기
                if (b_next.dest >= r_next.dest) {
                    b_next.y -= ydir[i];
                    b_next.x -= xdir[i];
                }
                else if (b_next.dest < r_next.dest) {
                    r_next.y -= ydir[i];
                    r_next.x -= xdir[i];
                }
            }

            red_m.push(r_next);
            blue_m.push(b_next);

        }

    }
    return -1;
}

marble move_m(marble m, int dir) {

    // 구슬을 한방향으로 이동시키고 구멍이나 벽을 만났을 때 해당 정보들을 내보내주기
    int y = m.y, x = m.x;
    int dest = m.dest;

    while (1) {
        y += ydir[dir];
        x += xdir[dir];
        dest += 1;
        if (MAP[y][x] == 'O') {
            m.y = y, m.x = x;
            m.dest = dest;
            return m;
        }
        // 만약에 벽에 도달하면 한칸 빼주기
        if (MAP[y][x] == '#' || y < 0 || x < 0 || y >= N || x >= M) {
            m.y = y - ydir[dir];
            m.x = x - xdir[dir];
            m.dest = dest - 1;
            return m;
        }
    }

}