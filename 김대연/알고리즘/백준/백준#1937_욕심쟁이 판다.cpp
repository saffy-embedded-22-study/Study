/*
dfs 이용해서 막히면 돌아오면서 +1 하면서 DAT에 값 저장하기
*/

#include<bits/stdc++.h>
using namespace std;

int diry[4] = { -1,1,0,0 };
int dirx[4] = { 0,0,-1,1 };

int N;
int Map[501][501];
int DAT[501][501];
int Ans;

void init();
int dfs(int y, int x);


int main() {
	ios::sync_with_stdio(false);
	cin.tie(NULL);

	init();
	
	for (int i = 0; i < N; ++i) {
		for (int j = 0; j < N; ++j) {
			if (DAT[i][j] == 0) {	// DAT 값이 없으면 dfs 돌리기!
				dfs(i, j);
			}
		}
	}
	cout << Ans;
	return 0;
}

void init() {
	cin >> N;

	for (int i = 0; i < N; ++i) {
		for (int j = 0; j < N; ++j) {
			cin >> Map[i][j];
		}
	}
}

int dfs(int y, int x) {

	int now = Map[y][x];

	bool flag = false;	// 갈 수 없는곳이 없으면 False 유지

	int Max = 0;

	for (int dir = 0; dir < 4; ++dir) {
		int dy = y + diry[dir];
		int dx = x + dirx[dir];
		if (dy < 0 || dx < 0 || dy >= N || dx >= N)continue;
		if (Map[dy][dx] <= now)continue;
		flag = true;

		if (DAT[dy][dx] != 0) {	// 값이 이미 있으면 dfs 들어갈 필요 없음!
			Max = max(DAT[dy][dx], Max);	
		}
		else {
			int next = dfs(dy, dx);
			Max = max(next, Max);
		}

	}

	if (!flag) {
		DAT[y][x] = 1;	// 막히면 1 리턴
	}
	else {
		DAT[y][x] = Max + 1;	// 아니면 지난 경로 값 + 1
	}
	Ans = max(Ans, DAT[y][x]);	// 최대값 갱신
	return DAT[y][x];
}
