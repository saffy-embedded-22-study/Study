// 2032kb 0ms
#include <iostream>
#include <algorithm>
using namespace std;

int n;

int red, green, blue;

int dp[1001][3];

int ans;

int main()
{
	ios::sync_with_stdio(false);
	cin.tie(NULL); cout.tie(NULL);

	cin >> n;

	dp[0][0] = 0; // i번째에 red를 선택한 경우
	dp[0][1] = 0; // i번째에 green을 선택한 경우
	dp[0][2] = 0; // i번째에 blue를 선택한 경우

	for (int i = 1; i <= n; ++i)
	{
		cin >> red >> green >> blue;
		
		//매번 최솟값 저장
		dp[i][0] = min(dp[i - 1][1], dp[i - 1][2]) + red;
		dp[i][1] = min(dp[i - 1][0], dp[i - 1][2]) + green;
		dp[i][2] = min(dp[i - 1][0], dp[i - 1][1]) + blue;
	}

	// 3가지 경우에 대해서 최솟값 찾기
	ans = min(dp[n][2], min(dp[n][0], dp[n][1]));

	cout << ans;

	return 0;
}