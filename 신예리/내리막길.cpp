#include <iostream>
using namespace std;

int MAP[501][501];
int DP[501][501];
int N, M;
int ydir[4] = { -1, 1, 0, 0 };
int xdir[4] = { 0, 0, -1, 1 };

int dfs(int, int);

int main() {

	ios::sync_with_stdio(false);
	cin.tie(NULL); cout.tie(NULL);

	cin >> N >> M;
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < M; j++) {
			cin >> MAP[i][j];
			DP[i][j] = -1;
		}
	}

	cout << dfs(0, 0) << '\n';

	return 0;
}

int dfs(int y, int x) {

	if (y == N - 1 && x == M - 1) {
		return 1; //종점이라면 1을 반환
	}
	if (DP[y][x] != -1) //이미 방문한 곳이라면 해당 DP값 리턴
		return DP[y][x];

	DP[y][x] = 0;
	for (int i = 0; i < 4; i++) {
		int ny = y + ydir[i];
		int nx = x + xdir[i];

		if (ny < 0 || nx < 0 || ny >= N || nx >= M)continue;

		if (MAP[y][x] > MAP[ny][nx])
			DP[y][x] += dfs(ny, nx);

	}
	return DP[y][x];
}