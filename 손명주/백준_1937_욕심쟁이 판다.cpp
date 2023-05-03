#include <iostream>
using namespace std;

int N; //4040kb 120ms
int Map[500][500];
int Dp[500][500]; //최소 1, 최대값
int dir[4][2] = { -1,0,1,0,0,-1,0,1 };

int Find(int y, int x); //y,x에서 최댓값

int main() {
	cin >> N;
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			cin >> Map[i][j];
		}
	}
	int ans = 0;
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			int now = Find(i, j);
			if (ans < now) ans = now;
		}
	}
	cout << ans;
	return 0;
}
int Find(int y, int x) { //상하좌우 중에 큰 거 + 1
	if (Dp[y][x] != 0) return Dp[y][x];

	int maxdp = 0;
	for (int i = 0; i < 4; i++) {
		int ny = y + dir[i][0];
		int nx = x + dir[i][1];
		if (ny < 0 || nx < 0 || ny >= N || nx >= N) continue;
		if (Map[ny][nx] <= Map[y][x]) continue; //더 많은 나무만
		
		int here = Find(ny, nx);
		if (maxdp < here) maxdp = here;
	}

	return Dp[y][x] = maxdp + 1;
}