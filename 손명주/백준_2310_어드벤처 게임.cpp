#include <iostream>
#include <algorithm>
#include <vector>
#include <cstring>
using namespace std;

int N; // 2712kb 72ms
int costs[1000]; // 0 빈방 + 레플리콘 - 트롤
int money[1000]; //   money[i] | i번째 방들어갔을 때 남은 돈
vector<int> al[1000]; // al[i] | i번째 방에서 이어진 방

void dfs(int);

int main() {
	ios::sync_with_stdio(false);
	cin.tie(NULL); cout.tie(NULL);

	while (1) {
		memset(costs, 0, sizeof(costs));
		memset(money, -1, sizeof(money));

		cin >> N;
		if (N == 0) break;

		char room; int cost;
		for (int i = 0; i < N; i++) {
			cin >> room; cin >> cost;
			if (room == 'T') costs[i] = -cost;
			else costs[i] = cost;

			int to;
			while (1) {
				cin >> to;
				if (to == 0) break;
				al[i].push_back(to - 1);
			}
		}
		money[0] = costs[0];
		dfs(0);
		if (money[N - 1] == -1) cout << "No\n";
		else cout << "Yes\n";

		for (int i = 0; i < N; i++) al[i].clear();
	}
	return 0;
}
void dfs(int from) {
	int way = al[from].size();

	for (int i = 0; i < way; i++) {
		int to = al[from][i];
		int left = money[from] + costs[to]; //넘어갔을 때 남는 돈
		if (costs[to] > 0) left = max(money[from], costs[to]);

		if (left < 0) continue;
		if (money[to] < left) { //처음가보거나 더 이득인 경우만 넘어가기
			money[to] = left;
			if (to == N - 1) return;
			dfs(to);
		}
	}
}