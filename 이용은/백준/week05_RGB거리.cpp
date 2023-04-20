#include <iostream>
#include <algorithm>
#define MAX_N 1001

using namespace std;
int dp[MAX_N][3];
int color[MAX_N][3];
int N;

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(0);

	cin >> N;
	for (int i = 1; i <= N; i++) {
		cin >> color[i][0]>>color[i][1]>>color[i][2];
	}

	//dp[0] -> 모두 0
	for (int i = 1; i <= N; i++) {

		for (int j = 0; j < 3; j++) {
			int minCost = 21e8;
			for (int k = 0; k < 3; k++) {
				if (k == j)continue;//자기자신은 선택 불가
				if (minCost > dp[i - 1][k]) {
					minCost = dp[i - 1][k];
				}
			}
			dp[i][j] = color[i][j] + minCost;//현재값 + 나머지 색중 최솟값
		}
	}
	cout << min({ dp[N][0] ,dp[N][1], dp[N][2]});

}