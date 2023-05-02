/* 최대한 많은 칸을 방문하는 것을 정하는 문제이므로
dp[y][x]에는 (y,x)에서 출발했을 때 최대로 방문할 수 있는 값을 저장해야한다.
*/


#include <iostream>
#include <algorithm>
using namespace std;

int n;
int bamboo[501][501];
int dp[501][501];
int ydir[4] = { -1,0,1,0 };
int xdir[4] = { 0,-1,0,1 };

void input()
{
	cin >> n;

	for (int i = 0; i < n; ++i)
	{
		for (int j = 0; j < n; ++j)
		{
			cin >> bamboo[i][j];
			dp[i][j] = 1; // 모든 칸에는 최소 한번은 방문 가능하기 때문에 1로 초기화
		}
	}
}

int func(int y, int x) // (y,x)에서 출발했을 때의 최대 방문 칸 return
{
	// 1이 아닌 경우는 이미 그 칸에서 방문할 수 있는 최대로 방문할 수 있는 칸의 값이 저장되어 있기 때문에 
	// dp[y][x] 값 return
	if (dp[y][x] != 1)
		return dp[y][x];


	int MAX = 1; // dp가 가질 수 있는 최솟값

	for (int i = 0; i < 4; ++i)
	{
		int ny = y + ydir[i];
		int nx = x + xdir[i];

		if (ny < 0 || nx < 0 || ny >= n || nx >= n) continue;
		if (bamboo[ny][nx] <= bamboo[y][x]) continue; // 다음 칸의 대나무가 현재 칸의 대나무보다 같거나 작은 경우 무시
		int temp = func(ny, nx) + 1;

		MAX = max(MAX, temp);
	}
	
	return dp[y][x] = MAX;
}

int main()
{
	input();

	int ans = -21e8;
	for (int i = 0; i < n; ++i)
	{
		for(int j = 0; j<n; ++j)
		{
			ans = max(ans, func(i,j)); // 모든 칸에서 확인
		}
	}

	cout << ans;
	return 0;
}
