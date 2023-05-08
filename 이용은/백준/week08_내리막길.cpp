#include <iostream>
#define MAX_N 500
using namespace std;
int N, M;
int Map[MAX_N][MAX_N];
int dp[MAX_N][MAX_N];
int visited[MAX_N][MAX_N];

void init();
int dfs(int, int);

int main() {
	init();
	visited[0][0] = 1;
	cout << dfs(0, 0);
	return 0;
}

void init() {
	ios_base::sync_with_stdio(false);
	cin.tie(0);
	cin >> N >> M;
	for (int y = 0; y < N; y++) {
		for (int x = 0; x < M; x++) {
			cin >> Map[y][x];
			dp[y][x] = 21e8;
		}
	}
}

int dfs(int nowY, int nowX) {
	//base
	if (nowY == N - 1 && nowX == M - 1) {
		return 1;
	}
	if (dp[nowY][nowX] != 21e8) {
		return dp[nowY][nowX];
	}
	
	//recursive
	int ydir[] = { -1,1,0,0 };
	int xdir[] = { 0,0,-1,1 };

	int temp = 0;
	for (int i = 0; i < 4; i++) {
		int ny = nowY + ydir[i];
		int nx = nowX + xdir[i];
		if (ny >= N || ny < 0 || nx >= M || nx < 0) continue;
		if (Map[ny][nx] < Map[nowY][nowX]) {
			if (visited[ny][nx] == 1) continue;
			visited[ny][nx] = 1;
			temp +=dfs(ny, nx);
			visited[ny][nx] = 0;
			
		}
	}
	return dp[nowY][nowX] = temp;
}