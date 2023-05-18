#include <iostream>
#include <cmath>
#include <algorithm>
using namespace std;
int N;
int cost[16][16];
int dp[1 << 15][16];
int fullV;

int dfs(int now, int V) {

	if (V == fullV) {//모두 방문한 경우
		if (cost[now][0] != 0) return cost[now][0];//시작노드와 이어지면
		else return 21e8;//아니면 -> 불가능
	}
	if (dp[V][now] != 0) return dp[V][now];

	int temp = 21e8;

	for (int i = 1; i < N; i++) { //시작노드는 방문 X
		int next = i;
		if (cost[now][next] == 0) continue;//연결 안된경우 pass
		if (((V >> (next - 1)) & 1) == 1) continue;//방문한 경로 pass
		int newV = V | (1 << (next - 1));

		temp = min(temp, dfs(next,newV) + cost[now][next]);
	}

	return dp[V][now] = temp;
}

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(0);

	cin >> N;
	for (int y = 0; y < N; y++) {
		for (int x = 0; x < N; x++) {
			cin >> cost[y][x];
		}
	}
	fullV = pow(2, N-1)-1;
	
	cout << dfs(0,0);
	return 0;
}