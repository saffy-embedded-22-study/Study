//2176KB 0ms
#include <iostream>
#include <string>
#include <queue>
using namespace std;

int n;

int maze[51][51];
int visited[51][51];

struct node
{
	int y;
	int x;
	int change; // 검은 블록 지나간 횟수
	bool operator<(node next)const
	{
		if (change > next.change)return true;
		if (change < next.change)return false;
		return false;
	}
};

int ydir[4] = { -1,0,1,0 };
int xdir[4] = { 0,-1,0,1 };

void input()
{
	cin >> n;

	for (int i = 0; i < n; ++i)
	{
		string s; cin >> s;
		for (int j = 0; j < n; ++j)
		{
			maze[i][j] = (int)s[j] - 48; //char to int
			visited[i][j] = 21e8; // visited 초기값 설정
		}
	}
}

int bfs()
{
	priority_queue<node> pq;
	pq.push({ 0,0,0 });
	visited[0][0] = 0;

	while (!pq.empty())
	{
		node now = pq.top(); pq.pop();

		if (visited[now.y][now.x] < now.change)continue; 

		int cnt = 0;

		for (int i = 0; i < 4; ++i)
		{
			int ny = now.y + ydir[i];
			int nx = now.x + xdir[i];
			int nchange = now.change;

			if (ny < 0 || nx < 0 || ny >= n || nx >= n) continue;
			if (visited[ny][nx] <= nchange) continue;
			if (!maze[ny][nx]) nchange++;

			visited[ny][nx] = nchange;
			pq.push({ ny,nx,nchange });
		}
	}

	return visited[n - 1][n - 1]; // 위에서 온 경우와 왼쪽에서 온 경우 둘 중 작은 값을 뽑아야하므로 queue를 다 돌고 출력
}

int main()
{
	ios::sync_with_stdio(false);
	cin.tie(NULL); cout.tie(NULL);

	input();
	cout << bfs();

	return 0;
}
