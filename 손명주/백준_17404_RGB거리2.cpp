#include <iostream>
#include <cstring>
#include <algorithm>
using namespace std;

int N;
int Cost[1000][3];
int dp[1000][3];
int ans;

void Paint(int start) {//첫 번째 집 start 색으로 칠할 때
	memset(dp, 0, sizeof(dp));
	dp[0][start] = Cost[0][start];
	dp[0][(start + 1) % 3] = 2000; //선택되지 않게 최소보다 큰 값 넣어줌
	dp[0][(start + 2) % 3] = 2000;
	for (int i = 1; i < N; i++) {
		for (int j = 0; j < 3; j++) {
			dp[i][j] = min(dp[i - 1][(j + 1) % 3] + Cost[i][j], dp[i - 1][(j + 2) % 3] + Cost[i][j]);
		}
	}
	int res = min(dp[N - 1][(start + 1) % 3], dp[N - 1][(start + 2) % 3]);
	if (ans > res) ans = res;
	return;
}
int main() {
	cin >> N;
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < 3; j++) {
			cin >> Cost[i][j];
		}
	}
	ans = 9999999;
	for (int i = 0; i < 3; i++) Paint(i);
	cout << ans;
	return 0;
}