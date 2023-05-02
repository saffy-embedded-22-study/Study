#include <iostream>
using namespace std;

int n;
int MAP[501][501];
int dp[501][501];
int result;

int ydir[4] = { -1,1,0,0 };
int xdir[4] = { 0,0,-1,1 };

int dfs(int, int);

int main() {

    ios::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);

    cin >> n;

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cin >> MAP[i][j];
        }
    }

    // 모든 좌표에서 최대값 갱신
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            int cnt = dfs(i, j);
            result = max(cnt, result);
        }
    }

    cout << result;

    return 0;

}

int dfs(int y, int x) {

    if (dp[y][x] == 0) { // 값이 저장된 적이 없는 경우
        dp[y][x] = 1; // 한 칸은 무조건 방문 가능 
        int bamcnt = 1; // 몇 칸을 더 갈 수 있는 지 체크
        for (int i = 0; i < 4; i++) {
            int ny = y + ydir[i];
            int nx = x + xdir[i];

            if (ny < 0 || nx < 0 || ny >= n || nx >= n)continue;
            if (MAP[ny][nx] > MAP[y][x]) { // 다음칸이 더 큰경우에
                bamcnt = max(bamcnt, dfs(ny, nx) + 1); // 현재 좌표에서 갈 수 있는 칸의 수 중 가장 큰 값
            }

        }
        dp[y][x] = bamcnt; // 해당 값을 현재 dp에 넣어주기
    }

    return dp[y][x];

}