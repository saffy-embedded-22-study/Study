#include <iostream>
#include <algorithm>
using namespace std;

int house_dp[1001][3];
int N;
int color[3]; // red,green,blue

int main() {

	ios::sync_with_stdio(false);
	cin.tie(NULL); cout.tie(NULL);

	cin >> N;

	house_dp[0][0] = 0; // 빨강으로 칠했을 때
	house_dp[0][1] = 0; // 초록으로 칠했을 때
	house_dp[0][2] = 0; // 파랑으로 칠했을 때


	for (int i = 1; i <= N; i++)
	{
		cin >> color[0] >> color[1] >> color[2];

		house_dp[i][0] = min(house_dp[i - 1][1], house_dp[i - 1][2]) + color[0]; // i번째를 빨강으로 칠했을 때 => 이전 집이 초록/파랑
		house_dp[i][1] = min(house_dp[i - 1][0], house_dp[i - 1][2]) + color[1]; // i번째를 초록으로 칠했을 때 => 이전 집이 빨강/파랑
		house_dp[i][2] = min(house_dp[i - 1][0], house_dp[i - 1][1]) + color[2]; // i번째를 파랑으로 칠했을 때 => 이전 집이 빨강/초록
	}

	cout << min({ house_dp[N][0], house_dp[N][1], house_dp[N][2] }); // 세 경우 중에 최소값

}