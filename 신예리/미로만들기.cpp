#include <iostream>
#include <queue>
using namespace std;

struct yx {
    int y;
    int x;
};

int n;
char MAP[52][52]; // 방에 대한 정보 1: 흰방 0: 검은방
int change_cnt[52][52]; // 뚫고 온 개수 저장
int ydir[4] = { 1, -1, 0, 0 };
int xdir[4] = { 0, 0, -1, 1 };

void bfs(int, int);

int main() {

    ios::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);

    cin >> n;

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            char a;
            cin >> a;
            MAP[i][j] = a;
            change_cnt[i][j] = 999999; // 최소값 갱신을 위해서 큰 값 넣어주기
        }
    }

    bfs(0, 0);

    cout << change_cnt[n - 1][n - 1] << '\n';

    return 0;
}

void bfs(int y, int x) {

    queue<yx> q;
    q.push({ y,x });
    change_cnt[y][x] = 0; // 시작 점은 0

    while (!q.empty()) {
        yx now = q.front();
        q.pop();

        for (int i = 0; i < 4; i++) {
            int ny = now.y + ydir[i];
            int nx = now.x + xdir[i];
            if (ny < 0 || nx < 0 || ny >= n || nx >= n)continue;

            if (MAP[ny][nx] == '1') { // 흰 방 => 뚫고 온 방의 개수 비교 최소값 갱신
                if (change_cnt[ny][nx] > change_cnt[now.y][now.x]) {
                    change_cnt[ny][nx] = change_cnt[now.y][now.x];
                    q.push({ ny,nx });
                }
            }
            else if (MAP[ny][nx] == '0') { //검은 방 => 뚫고 온방 개수 비교 최소값 갱신
                if (change_cnt[ny][nx] > change_cnt[now.y][now.x] + 1) {
                    change_cnt[ny][nx] = change_cnt[now.y][now.x] + 1;
                    q.push({ ny,nx });
                }

            }
        }
    }
}