#include <iostream>
#include <cstring>
#include <algorithm>
#include <string>
#include <vector>
#include <queue>
using namespace std;

// no_virus : 빈칸의 개수, result : 각각의 케이스에 대한 답
//ans: 최종 답, Size: virus의 개수 
int n, m, no_virus, result, ans, Size;

int lab[51][51];
int visited[51][51];

int ydir[4] = { -1,0,1,0 };
int xdir[4] = { 0,-1,0,1 };

struct node {
	int y;
	int x;
};

struct info {
	int y;
	int x;
	int time;
};

vector<node>virus;
vector<node>target_virus;
queue<info>q;

void infection()
{
	//cnt에 값 저장
	int cnt = no_virus;

	//queue 초기화
	while (!q.empty())
		q.pop();


	//target_virus에서 대상 바이러스들 queue에 추가
	for (int i = 0; i < m; ++i)
	{
		int y = target_virus[i].y; int x = target_virus[i].x;
		q.push({ y,x,0 });
		visited[y][x] = 1;
	}

	result = 0;



	while (!q.empty())
	{
		info now = q.front(); q.pop();

		//가지치기
		if (result >= ans) return;

		for (int i = 0; i < 4; ++i)
		{
			//빈칸이 없는 경우 ans 값 갱신 후 return
			if (cnt == 0)
			{
				ans = min(ans, result);
				return;
			}

			int ny = now.y + ydir[i];
			int nx = now.x + xdir[i];
			int ntime = now.time + 1;
			result = ntime;

			if (ny < 0 || nx < 0 || ny >= n || nx >= n) continue;
			if (visited[ny][nx]) continue;
			if (lab[ny][nx] == 1) continue; // 벽이 있을 때

			if (lab[ny][nx] == 0) cnt--; //빈칸이 지워질 때 cnt 감소
			visited[ny][nx] = ntime;
			q.push({ ny,nx,ntime });
		}


	}
	return;
}

//조합으로 바이러스 선택
void choose_virus(int level, int now)
{
	if (level == m)
	{
		memset(visited, 0, sizeof(visited));
		infection();
		return;
	}

	for (int i = now; i < Size; ++i)
	{
		target_virus.push_back({ virus[i].y, virus[i].x });
		choose_virus(level + 1, i + 1);
		target_virus.pop_back();
	}
}

int main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(NULL); cout.tie(NULL);

	cin >> n >> m;

	virus.reserve(11);
	target_virus.reserve(11);

	no_virus = 0;
	ans = 21e8;

	for (int i = 0; i < n; ++i)
	{
		for (int j = 0; j < n; ++j)
		{
			cin >> lab[i][j];
			if (lab[i][j] == 0)
				no_virus++;
			if (lab[i][j] == 2)
				virus.push_back({ i,j });
		}
	}

	Size = virus.size();
	choose_virus(0, 0);

	if (ans == 21e8)
		cout << "-1";
	else
		cout << ans;
}