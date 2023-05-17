#include <iostream>
#include <math.h>
using namespace std;

int N; //10024kb 28ms
int dp[100000][20]; //y 축 0x0010 이면 1번만 가본 경로
int costs[20][20];
int arrive;

int Go(int path, int from) {
	if (path == arrive && costs[from][0] != 0) return costs[from][0];
	if (dp[path][from] != 0) return dp[path][from];

	int minCost = 10000000;
	for (int to = 1; to < N; to++) {
		int cost = costs[from][to];
		if (cost == 0) continue; //못가는 곳
		if ((path >> to) & 1 == 1) continue; //갔던 곳

		int npath = path ^ (1 << to);
		int ncost = Go(npath, to) + costs[from][to];
		if (minCost > ncost) minCost = ncost;
	}
	return dp[path][from] = minCost;
}
int main() {
	cin >> N;
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			cin >> costs[i][j];
		}
	}
	arrive = pow(2, N) - 2; //N=4 일때 0x1110
	cout << Go(0, 0);
	return 0;
}