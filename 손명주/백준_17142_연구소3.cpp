#include <iostream>
#include <cstring>
#include <vector>
#include <queue>
using namespace std;

int N, M;
int MAP[50][50]; //0빈칸 1벽 2바이러스
int visit[50][50];
int n; //바이러스 수
int cnt; //빈칸 수
int ans;
int dir[4][2] = { -1,0,1,0,0,-1,0,1 };
struct node {
	int y;
	int x;
};
vector<node> can;
vector<node> virus;


int Fill() {
	memset(visit, 0, sizeof(visit));
	queue<node> q;
	int Time = 0;
	int left = cnt;
	if (left == 0) return Time;

	for (int i = 0; i < M; i++) { //바이러스 큐에 넣어주기
		node v = virus[i];
		q.push({ v.y, v.x });
		visit[v.y][v.x] = 1;
	}
	while (!q.empty()) {
		int cursize = q.size();

		for (int c = 0; c < cursize; c++) {
			node now = q.front();
			q.pop();

			for (int i = 0; i < 4; i++) {
				int ny = now.y + dir[i][0];
				int nx = now.x + dir[i][1];
				if (ny < 0 || nx < 0 || ny >= N || nx >= N) continue;
				if (visit[ny][nx] == 1) continue;
				
				int next = MAP[ny][nx];
				if (next == 1) continue;
				if (next == 0) left--;
				visit[ny][nx] = 1;

				q.push({ ny,nx });
			}
		}
		Time++;
		if (left == 0) return Time;
	}
	return -1;
	
}
void Put(int vn, int to) {
	if (vn == M) {
		int res = Fill();
		if (res >= 0 && ans > res) ans = res;
		return;
	}
	for (int i = to; i < n; i++) {
		node now = can[i];
		virus.push_back({ now.y, now.x });
		Put(vn + 1, i + 1);
		virus.pop_back();
	}
}
int main() {
	cin >> N >> M;
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			int a; cin >> a;
			MAP[i][j] = a;
			if (a == 2) {
				can.push_back({ i,j });
				n++;
			}
			if (a == 0) cnt++;
		}
	}
	ans = 9999;
	Put(0, 0);
	if (ans == 9999) ans = -1;
	cout << ans;

	return 0;
}