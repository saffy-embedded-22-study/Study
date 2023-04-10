/*
info라는 구조체에 상어의 정보들을 담아
모든 상어를 탐색하면서 문제에서 요구하는 동작을 실행하는 방법으로
코드를 구상하였습니다.

*/


#include <iostream>
#include <vector>
#include <cstring>
#include <algorithm>
using namespace std;

int R, C, m, ans;

int visited[101][101];

struct info
{
	int y;
	int x;
	int speed;
	int dir;
	int mass;
	int alive;
};

struct targeting
{
	int y;
	int idx;
};

targeting target;

vector<info>shark;

int ydir[5] = { 0,-1,1,0,0 };
int xdir[5] = { 0,0,0,1,-1 };

int change_dir(int d)
{
	if (d == 1) return 2;
	if (d == 2) return 1;
	if (d == 3) return 4;
	if (d == 4) return 3;
}

void input()
{
	cin >> R >> C >> m;

	ans = 0;
	target = { R+1,-1 };

	for (int i = 0; i < m; ++i)
	{
		int r, c, s, d, z;
		cin >> r >> c >> s >> d >> z;

		//무의미하게 반복되는 움직임을 제거하기 위한 식
		if (d == 1 || d == 2) s %= (2 * R - 2);
		if (d == 3 || d == 4) s %= (2 * C - 2); 

		shark.push_back({ r,c,s,d,z,1 });
		
		//땅에 제일 가까운 상어 찾기
		if (c == 1)
		{
			if (r < target.y)
				target = { r,i };
		}
	}
}



void fishing()
{
	for (int i = 1; i <= C; ++i)
	{
		memset(visited, -1, sizeof(visited));

		//낚시
		//해당 열에 존재하는 땅과 가까운 상어를 잡는다.
		if (target.idx != -1)
		{
			shark[target.idx].alive = 0;
			ans += shark[target.idx].mass;
		}
		
		target = { R+1,-1 };


		for (int j = 0; j < m; ++j)
		{
			info now = shark[j];

			//alive라는 정보를 통해 죽었는지 살았는지 확인
			if (!now.alive) continue;

			int y = now.y;
			int x = now.x;
			int speed = now.speed;
			int dir = now.dir;
			int mass = now.mass;


			int ny = y;
			int nx = x;

	   	 	//상어 이동
			//상어가 이동할 좌표 설정
			while (speed--)
			{
				ny = y + ydir[dir];
				nx = x + xdir[dir];
				if (ny <= 0 || nx <= 0 || ny > R || nx > C)
				{
					dir = change_dir(dir);
					ny = y + ydir[dir];
					nx = x + xdir[dir];
				}
				y = ny;
				x = nx;
			}

			//visited가 0이상인 경우(이동할 좌표에 이미 상어가 존재하는 경우)
			if (visited[ny][nx] >= 0)
			{
				//크기를 비교하여 visited의 정보와 상어의 정보를 변경
				if (mass > shark[visited[ny][nx]].mass)
				{
					shark[visited[ny][nx]].alive = 0;
					shark[j].y = ny;
					shark[j].x = nx;
					shark[j].dir = dir;
					visited[ny][nx] = j;
				}
				else
					shark[j].alive = 0;
			}
			else
			{
				visited[ny][nx] = j;
				shark[j].y = ny;
				shark[j].x = nx;
				shark[j].dir = dir;
			}
		}

		//상어가 이동을 다 끝냈기 때문에 다음 열에 존재하는
		//상어의 정보를 확인하여 target 설정
		for (int j = 0; j < m; ++j) {
			info now = shark[j];

			if (!now.alive) continue;
			if (now.x == i + 1) {
				if (target.y >= now.y) {
					target = { now.y, j };
				}
			}

		}
	}
}

int main()
{
	ios::sync_with_stdio;
	cin.tie(NULL); cout.tie(NULL);

	input();
	fishing();

	cout << ans;

	return 0;
}
