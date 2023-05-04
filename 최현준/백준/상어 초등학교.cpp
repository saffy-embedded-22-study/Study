//2168kb 4ms
#include <iostream>
#include <vector>
#include <queue>
using namespace std;

int n,ans;
int ydir[4] = { -1,0,1,0 };
int xdir[4] = { 0,1,0,-1 };
int classroom[21][21] = { 0, };
int order[401];
vector<int>student[401];

struct node
{
	int y;
	int x;
	int good; // 인접한 곳에 좋아하는 애들 수
	int empty; // 인접한 비어있는 칸
	bool operator<(node next)const 
	{
		if (good < next.good)return true;
		if (good > next.good)return false;
		if (empty < next.empty) return true;
		if (empty > next.empty) return false;
		if (y < next.y) return false;
		if (y > next.y) return true;
		if (x < next.x) return false;
		if (x > next.x) return true;
		return false;
	}
};


void input()
{
	cin >> n;
	ans = 0;
	for (int i = 0; i < n*n; ++i)
	{
		cin >> order[i];

		for (int j = 0; j < 4; ++j)
		{
			int person; cin >> person;
			student[order[i]].push_back(person);
		}
	}
}

void place()
{
	for (int idx = 0; idx < n*n; ++idx)
	{
		priority_queue<node> pq;
		for (int i = 0; i < n; ++i)
		{
			for (int j = 0; j < n; ++j)
			{
				if (classroom[i][j]) continue; // 이미 자리에 학생이 있으면 pass

				int empty = 0;
				int good = 0;
				for (int dir = 0; dir < 4; ++dir) // 4방향 search 해서 빈공간, 좋아하는 아이가 있는지 확인
				{
					int ny = i + ydir[dir];
					int nx = j + xdir[dir];

					if (ny < 0 || nx < 0 || ny >= n || nx >= n) continue;
					if (classroom[ny][nx] == 0) {
						empty++;
						continue;
					}

					for (int k = 0; k < 4; ++k)
					{
						if (classroom[ny][nx] == student[order[idx]][k])
							good++;
					}
				}
				pq.push({ i,j,good,empty }); // 빈 공간에 대해서 pq에 정렬
			}
		}

		node now = pq.top();

		classroom[now.y][now.x] = order[idx]; // 조건에 맞는 자리에 학생 앉히기
	}


}


void calc() // 조건에 맞게 만족도 설정
{
	for (int i = 0; i < n; ++i)
	{
		for (int j = 0; j < n; ++j)
		{
			int cnt = 0;
			for (int d = 0; d < 4; ++d)
			{
				int ny = i + ydir[d];
				int nx = j + xdir[d];
				if (ny < 0 || nx < 0 || ny >= n || nx >= n) continue;
				for (int k = 0; k < 4; ++k)
				{
					if (classroom[ny][nx] == student[classroom[i][j]][k])
						cnt++;
				}
			}

			if (cnt == 1) ans += 1;
			else if (cnt == 2) ans += 10;
			else if (cnt == 3) ans += 100;
			else if (cnt == 4) ans += 1000;
		}
	}
}

int main()
{
	ios::sync_with_stdio(false);
	cin.tie(NULL); cout.tie(NULL);

	input();
	place();
	calc();
	cout << ans;

	return 0;
}