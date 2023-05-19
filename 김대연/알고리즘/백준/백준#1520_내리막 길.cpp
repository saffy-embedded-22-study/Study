#include <bits/stdc++.h>
using namespace std;

int diry[4] = {-1, 1, 0, 0};
int dirx[4] = {0, 0, -1, 1};

int N, M;
int Map[501][501];
int DP[501][501];

void init();
void dfs(int y, int x);

int main()
{
	ios::sync_with_stdio(false);
	cin.tie(NULL);

	init();

	dfs(0, 0);
	cout << DP[0][0];

	return 0;
}

void init()
{
	cin >> N >> M;
	for (int i = 0; i < N; ++i)
	{
		for (int j = 0; j < M; ++j)
		{
			cin >> Map[i][j];
		}
	}
	fill_n(&DP[0][0], 501 * 501, -1); // -1로 세팅
	DP[N - 1][M - 1] = 1;			  // 도착지 1
}

void dfs(int y, int x)
{

	int temp = 0;

	for (int dir = 0; dir < 4; ++dir)
	{
		int dy = y + diry[dir];
		int dx = x + dirx[dir];

		if (dy < 0 || dx < 0 || dy >= N || dx >= M)
			continue;
		if (Map[y][x] <= Map[dy][dx])
			continue;

		if (DP[dy][dx] != -1) // -1 일 경우에만 dfs 진행
		{
			temp += DP[dy][dx];
		}
		else
		{
			dfs(dy, dx);
			temp += DP[dy][dx];
		}
	}
	DP[y][x] = temp;
}