/*
배열을 선언하여 사무실의 정보를 받고
dfs를 이용하여 해결한다
각각의 cctv의 값에 따라 while문을 통해 감시할 수 있는 칸의 값을 -1로 결정하고
dfs return할 때 0(사각지대)의 개수를 세고 ans값을 갱신한다.
*/


#include <iostream>
#include <cstring>
#include <algorithm>
#include <string>
#include <vector>
using namespace std;

int n, m ,Size, ans;

int office[9][9];

int ydir[4] = { -1,0,1,0 };
int xdir[4] = { 0,1,0,-1 };

struct node {
	int y;
	int x;
	int value;
};

vector<node>cctv;


//level:cctv index, new_office:사무실 정보
void dfs(int level, int new_office [][9])
{
	if (level == Size)
	{
		int cnt = 0;
		for (int i = 0; i < n; ++i)
		{
			for (int j = 0; j < m; ++j)
			{
				if (new_office[i][j] == 0)
					cnt++;
			}
		}
		ans = min(ans, cnt);
		return;
	}
	
	//temp라는 임시배열을 선언하여 office의 값을 복사하여 받고
	//다음 dfs에 전달한다.
	int temp[9][9];
	copy(&new_office[0][0], &new_office[0][0] + 9 * 9, &temp[0][0]);
	//memcpy(temp, new_office, sizeof(new_office));

	int num = cctv[level].value;


	//1번 cctv
	if (num == 1)
	{
		for (int i = 0; i < 4; ++i)
		{
			int y = cctv[level].y;
			int x = cctv[level].x;
			while (1)
			{
				int ny = y + ydir[i];
				int nx = x + xdir[i];
				if (ny < 0 || nx < 0 || ny >= n || nx >= m) break;
				if (temp[ny][nx] == 6) break;
				if (temp[ny][nx] == 0) temp[ny][nx] = -1;
				y = ny; x = nx;
			}
			//각각의 방향에 따라 dfs를 하고 copy문으로 원래배열로 변경해줌.
			dfs(level + 1, temp);
			copy(&new_office[0][0], &new_office[0][0] + 9 * 9, &temp[0][0]);
		}
	}
	
	//2번 cctv
	else if (num == 2)
	{
		//위,아래 감시하는 경우
		for (int i = 0; i < 4; i += 2)
		{
			int y = cctv[level].y;
			int x = cctv[level].x;
			while (1)
			{
				int ny = y + ydir[i];
				int nx = x + xdir[i];
				if (ny < 0 || nx < 0 || ny >= n || nx >= m) break;
				if (temp[ny][nx] == 6) break;
				if (temp[ny][nx] == 0) temp[ny][nx] = -1;
				y = ny; x = nx;
			}
		}
		dfs(level + 1, temp);
		copy(&new_office[0][0], &new_office[0][0] + 9 * 9, &temp[0][0]);


		//왼쪽, 오른쪽 감시하는 경우
		for (int i = 1; i < 4; i += 2)
		{
			int y = cctv[level].y;
			int x = cctv[level].x;
			while (1)
			{
				int ny = y + ydir[i];
				int nx = x + xdir[i];
				if (ny < 0 || nx < 0 || ny >= n || nx >= m) break;
				if (temp[ny][nx] == 6) break;
				if (temp[ny][nx] == 0) temp[ny][nx] = -1;
				y = ny; x = nx;
			}
		}
		dfs(level + 1, temp);
		copy(&new_office[0][0], &new_office[0][0] + 9 * 9, &temp[0][0]);
	}
	
	//3번 cctv
	else if (num == 3)
	{
		for (int i = 0; i < 4; ++i)
		{
			//2방향 감시를 위한 for문
			for (int j = 0; j < 2; ++j) 
			{
				int y = cctv[level].y;
				int x = cctv[level].x;
				while (1)
				{
					int ny = y + ydir[(i+j)%4];
					int nx = x + xdir[(i+j)%4];
					if (ny < 0 || nx < 0 || ny >= n || nx >= m) break;
					if (temp[ny][nx] == 6) break;
					if (temp[ny][nx] == 0) temp[ny][nx] = -1;
					y = ny; x = nx;
				}
			}
			dfs(level + 1, temp);
			copy(&new_office[0][0], &new_office[0][0] + 9 * 9, &temp[0][0]);
		}
	}

	//4번 cctv
	else if (num == 4)
	{
		for (int i = 0; i < 4; ++i)
		{
			//3방향 감시를 위한 for문
			for (int j = 0; j < 3; ++j)
			{
				int y = cctv[level].y;
				int x = cctv[level].x;
				while (1)
				{
					int ny = y + ydir[(i + j) % 4];
					int nx = x + xdir[(i + j) % 4];
					if (ny < 0 || nx < 0 || ny >= n || nx >= m) break;
					if (temp[ny][nx] == 6) break;
					if (temp[ny][nx] == 0) temp[ny][nx] = -1;
					y = ny; x = nx;
				}
			}
			dfs(level + 1, temp);
			copy(&new_office[0][0], &new_office[0][0] + 9 * 9, &temp[0][0]);
		}
	}

	//5번 cctv
	else if (num == 5)
	{
		for (int i = 0; i < 4; ++i)
		{
			int y = cctv[level].y;
			int x = cctv[level].x;
			while (1)
			{
				int ny = y + ydir[i];
				int nx = x + xdir[i];
				if (ny < 0 || nx < 0 || ny >= n || nx >= m) break;
				if (temp[ny][nx] == 6) break;
				if (temp[ny][nx] == 0) temp[ny][nx] = -1;
				y = ny; x = nx;
			}
		}
		dfs(level + 1, temp);
		copy(&new_office[0][0], &new_office[0][0] + 9 * 9, &temp[0][0]);
	}
}


int main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(NULL); cout.tie(NULL);

	//vector capacity 설정
	cctv.reserve(81);

	cin >> n >> m;

	ans = 21e8;

	for (int i = 0; i < n; ++i)
	{
		for (int j = 0; j < m; ++j)
		{
			cin >> office[i][j];
			if (office[i][j] >= 1 && office[i][j] <= 5)
				cctv.push_back({ i,j,office[i][j] });
		}
	}

	//cctv 개수
	Size = cctv.size();

	dfs(0, office);

	if (ans == 21e8)
		cout << "0";
	else
		cout << ans;
}