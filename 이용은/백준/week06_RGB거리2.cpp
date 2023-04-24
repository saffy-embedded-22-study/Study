#include <iostream>
#include <algorithm>
#define MAX_N 1002
using namespace std;

int dp[MAX_N][3];
int color[MAX_N][3];

void input();
int run();
int N;

int main() {

	input();
	cout <<run();
	return 0;
}

void input() {
	ios_base::sync_with_stdio(false);
	cin.tie(0);
	cin >> N;
	for (int i = 1; i <= N; i++) {
		cin >> color[i][0] >> color[i][1] >> color[i][2];
	}
}

int run() {
	int ans = 21e8;
	for (int st = 0; st < 3; st++) {
		//초기화 -> 1번째 집 색깔 정하기
		dp[1][st] = color[1][st];
		for (int x = 0; x < 3; x++) {
			if (x == st) continue;
			dp[1][x] = 21e8;
		}
		//dp
		for (int i = 2; i <= N; i++) {
			
			for (int j = 0; j < 3; j++) {
				int minCost = 21e8;
				for (int k = 0; k < 3; k++) {
					if (j == k) continue;
					minCost = min(minCost,dp[i-1][k]);
				}
				dp[i][j] = color[i][j] + minCost;
			}
			
		}
		
		int ansTemp = 21e8;
		for (int end = 0; end < 3; end++) {
			if (st == end) continue;//처음 선택한 색(st)와 같은 색은 갱신 X
			ansTemp = min(ansTemp, dp[N][end]);
		}

		ans = min(ans, ansTemp);
	}
	return ans;
}