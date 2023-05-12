#include<bits/stdc++.h>
using namespace std;

int N;
int Map[17][17];
int FullVisit=1;
int DP[33000][15];	// [visited][현재위치]
int Ans = 21e8;

struct node {
	int now;
	int visited;	// 2~16 방문하면 1로
	int cost;

	bool operator < (node next) const {
		return cost > next.cost;
	}
};

priority_queue<node> pq;

void init();
void Solve();

int main() {
	ios::sync_with_stdio(false);
	cin.tie(NULL);

	init();

	Solve();

	cout << Ans;
	return 0;
}

void init() {
	cin >> N;
	for (int i = 1;i <= N;++i) {
		for (int j = 1;j <= N;++j) {
			cin >> Map[i][j];
		}
	}
	for (int i = 2;i < N;++i) {
		FullVisit = (FullVisit << 1) | 0x01;	// 1 제외하고 모두 방문했을때
	}
	fill_n(&DP[0][0], 33000 * 15, 21e8);
}

void Solve() {
	pq.push({ 1,0,0 });

	while (!pq.empty()) {
		node now = pq.top();
		pq.pop();

		if (now.visited == (FullVisit)) {
			if (Map[now.now][1] == 0)continue;
			if (Ans <= now.cost + Map[now.now][1]) continue;
			Ans = now.cost + Map[now.now][1];
			continue;
		}

		for (int i = 2;i <= N;++i) {	// 2부터 N 까지 이동
			// 방문 확인
			if (((now.visited >> (i - 2)) & (0x01)) == 1)continue;
			// 갈 수 있는지 확인
			if (Map[now.now][i] == 0)continue;	
			int nextVisit = now.visited | (0x01 << (i - 2));	// 방문처리
			if (DP[nextVisit][i] <= now.cost + Map[now.now][i]) continue;	// 값이 작을때만 이동
			DP[nextVisit][i] = now.cost + Map[now.now][i];
			pq.push({ i, nextVisit, DP[nextVisit][i]});
		}
	}


}