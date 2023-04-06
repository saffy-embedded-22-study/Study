#include <iostream>
#include <cstring>
#include <cmath>
#include <vector>
#include <queue>
#include <algorithm>
using namespace std;

int n, q;

int len,sum, max_block;

int field[64][64];
int visited[64][64];

struct node
{
	int y;
	int x;
};

int ydir[4] = { -1,0,1,0 };
int xdir[4] = { 0,-1,0,1 };

//배열 회전시키는 함수
void rotation(int line)
{
	int temp[64][64];

	//i,j 몇번째 격자 나타냄
	//k,l 격자 내의 인덱스

	for (int i = 0; i < len; i+=line)
	{
		for (int j = 0; j < len; j+=line)
		{
			for (int k = 0; k < line; ++k)
			{
				for (int l = 0; l < line; ++l)
					temp[k][l] = field[j + line - 1 - l][i + k]; //temp라는 임시 격자 안에 90도 회전
			}

			for (int k = 0; k < line; ++k)
			{
				for (int l = 0; l < line; ++l)
					field[j + k][i + l] = temp[k][l]; // field에 변경 값 넣기
			}

		}
	}
}


// 얼음 없애는 함수
void remove_ice()
{
	vector<node>ice;


	//2중 for문을 돌고 조건을 만족하는 칸을 ice라는 벡터에 추가한다.
	for (int i = 0; i < len; ++i)
	{
		for (int j = 0; j < len; ++j)
		{
			int cnt = 0;
			for (int d = 0; d < 4; ++d)
			{
				int ny = i + ydir[d];
				int nx = j + xdir[d];

				if (ny < 0 || nx < 0 || ny >= len || nx >= len || field[ny][nx] <= 0) cnt++;
			}
			if (cnt >= 2)
				ice.push_back({ i,j });
		}
	}


	//1씩 빼주기
	int ice_len = ice.size();

	for (int i = 0; i < ice_len; ++i)
	{
		int y = ice[i].y;
		int x = ice[i].x;

		field[y][x] --;
	}
}


//bfs 이용해서 제일 큰 덩어리 찾기
void big()
{
	queue<node>q;
	

	for (int i = 0; i < len; ++i)
	{
		for (int j = 0; j < len; ++j)
		{
			//모든 시작점을 기준으로 탐색하되 이미 방문한 칸과 얼음이 0인 칸은 제외
			if (visited[i][j] || field[i][j] <=0) continue;

			//아닌 경우 queue에 넣어서 탐색 시작
			q.push({ i,j });
			visited[i][j] = 1;
			int block = 1;

			while (!q.empty())
			{
				node now = q.front(); q.pop();

				for (int d = 0; d < 4; ++d)
				{
					int ny = now.y + ydir[d];
					int nx = now.x + xdir[d];

					if (visited[ny][nx]) continue;
					if (ny < 0 || nx < 0 || ny >= len || nx >= len || field[ny][nx] <= 0) continue;

					visited[ny][nx] = 1;
					block++;
					q.push({ ny,nx });
				}
			}

			//큰 덩어리 갱신
			max_block = max(block, max_block);
		}
	}
}

int main()
{
	ios::sync_with_stdio(false);
	cin.tie(NULL); cout.tie(NULL);

	cin >> n >> q;

	len = pow(2, n);

	for (int i = 0; i < len; ++i)
	{
		for (int j = 0; j < len; ++j)
			cin >> field[i][j];
	}


	//배열 회전하고 얼음 없애는 과정
	for (int i = 0; i < q; ++i)
	{
		int level; cin >> level;
		rotation(pow(2, level));
		remove_ice();
	}


	// 남아있는 얼음 합 구하기
	sum = 0;
	for (int i = 0; i < len; ++i)
	{
		for (int j = 0; j < len; ++j)
		{
			if (field[i][j] > 0) sum += field[i][j];
		}
	}

	max_block = -21e8;
	big();

	cout << sum << '\n';

	if (max_block == -21e8)
		cout << 0;
	else
		cout << max_block;


	return 0;
}