#include <iostream>
#include <vector>
#include <algorithm>
#define MAX_N 500
using namespace std;

int N;
int Map[MAX_N][MAX_N];
int dp[MAX_N][MAX_N];
int ydir[] = { -1,1,0,0 };
int xdir[] = { 0,0,-1,1 };

void init();
int sol();
int dfs(int, int);

int main() {
	init();
	cout << sol()+1;
	return 0;
}

void init() {
	ios_base::sync_with_stdio(false);
	cin.tie(0);
	cin >> N;
	for (int y = 0; y < N; y++) {
		for (int x = 0; x < N; x++) {
			cin >> Map[y][x];
			dp[y][x] = -1;
		}
	}
}

int sol() {
	int ans = -1;
	for (int y = 0; y < N; y++) {
		for (int x = 0; x < N; x++) {
			if (dp[y][x] != -1) continue;
			ans = max(dfs(y, x), ans);
		}
	}
	return ans;
}

int dfs(int nowY, int nowX) {
	
	if (dp[nowY][nowX] != -1) {
		return dp[nowY][nowX];
	}

	int temp = 0;
	for (int i = 0; i < 4; i++) {
		int ny = nowY + ydir[i];
		int nx = nowX + xdir[i];
		if (ny >= N || nx >= N || ny < 0 || nx < 0) continue;
		if (Map[ny][nx] <= Map[nowY][nowX]) continue;
		temp = max(temp, dfs(ny, nx)+1);
		
	}
	return dp[nowY][nowX] = temp;
}

