/*
다이스트라 응용
검은 방 갈때마다 cost + 1 하면서 진행.
*/

#include<bits/stdc++.h>
using namespace std;

int diry[4] = { -1,1,0,0 };
int dirx[4] = { 0,0,-1,1 };

struct node {
	int y, x;
	int cost;

	bool operator < (node next) const {
		return cost > next.cost;
	}
};

int n;
int Map[50][50];
int DAT[50][50];


int main() {
	cin.tie(NULL);
	ios::sync_with_stdio(false);

	cin >> n;

	for (int i = 0; i < n; ++i) {
		string temp;
		cin >> temp;
		for (int j = 0; j < n; ++j) {
			Map[i][j] = temp[j] - '0';
		}
	}

	fill_n(&DAT[0][0], 50 * 50, 21e8);	// 초기값 Max로 설정

	priority_queue<node> pq;
	pq.push({ 0,0,0 });	// 0,0 출발

	while (!pq.empty()) {
		node now = pq.top();
		pq.pop();

		if (now.y == n - 1 && now.x == n - 1) {	// 끝방 도착하면 종료
			cout << now.cost;
			return 0;
		}

		if (DAT[now.y][now.x] < now.cost) continue;

		for (int dir = 0; dir < 4; dir++) {
			int dy = now.y + diry[dir];
			int dx = now.x + dirx[dir];
			if (dy < 0 || dy >= n || dx < 0 || dx >= n)continue;

			int dcost = now.cost;

			if (Map[dy][dx] == 0) {	// 검은방이면 +1
				dcost++;
			}
			
			if (DAT[dy][dx] <= dcost)continue;
			DAT[dy][dx] = dcost;
			pq.push({ dy,dx,dcost });
		}
	}
	return 0;
}