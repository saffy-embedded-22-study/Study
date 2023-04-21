#include <iostream>
#include <algorithm>
using namespace std;

int N;
int Cost[1000][3];
int dp[1000][3];

int main() {
	cin >> N;
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < 3; j++) {
			cin >> Cost[i][j];
		}
	}
	for (int i = 0; i < 3; i++) dp[0][i] = Cost[0][i];

	for (int i = 1; i < N; i++) {
		dp[i][0] = min(dp[i - 1][1] + Cost[i][0], dp[i - 1][2] + Cost[i][0]);
		dp[i][1] = min(dp[i - 1][0] + Cost[i][1], dp[i - 1][2] + Cost[i][1]);
		dp[i][2] = min(dp[i - 1][1] + Cost[i][2], dp[i - 1][0] + Cost[i][2]);
	}

	int ans;
	ans = min({ dp[N - 1][0], dp[N - 1][1], dp[N - 1][2] });
	cout << ans;
	return 0;
}