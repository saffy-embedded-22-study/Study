#include <iostream>
#include <algorithm>
#include <queue>
#define MAX_W 200
using namespace std;
struct Node {
	int y, x, cost, cntK;

	bool operator < (Node next) const {
		if (cost < next.cost) return false;
		if (cost > next.cost) return true;
		return false;
	}
};

int K, W, H;
bool Map[MAX_W][MAX_W];
int dist[MAX_W][MAX_W][31];
int horseY[] = { -2, -2, -1,-1, 1, 1, 2, 2 };
int horseX[] = { -1, 1, -2, 2, -2, 2, -1, 1 };

int bfs();

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(0);
	cin >> K >> W >> H;

	for (int y = 0; y < H; y++) {
		for (int x = 0; x < W; x++) {
			cin >> Map[y][x];
		}
	}

	cout << bfs();

	return 0;
}

int bfs() {
	priority_queue<Node>pq;
	pq.push({ 0,0,0,0 });

	for (int y = 0; y < H; y++) {
		for (int x = 0; x < W; x++) {
			for (int i = 0; i <= K; i++) {
				dist[y][x][i] = 21e8;
			}
		}
	}

	dist[0][0][0] = 0;

	int ydir[]{ -1, 1, 0 ,0 };
	int xdir[]{ 0,0,-1,1 };

	while (!pq.empty()) {
		Node now = pq.top();
		pq.pop();

		if (now.cost > dist[now.y][now.x][now.cntK]) continue;
		if (now.y == H - 1 && now.x == W - 1) {
			return now.cost;
		}

		if (now.cntK < K) {
			for (int i = 0; i < 8; i++) {//말 처럼 이동

				int ny = now.y + horseY[i];
				int nx = now.x + horseX[i];
				if (ny >= H || ny < 0 || nx >= W || nx < 0) continue;
				if (Map[ny][nx] == 1) continue;

				int ncost = dist[now.y][now.x][now.cntK] + 1;
				if (ncost >= dist[ny][nx][now.cntK+1]) continue;
				dist[ny][nx][now.cntK + 1] = ncost;
				pq.push({ ny,nx,ncost,now.cntK + 1 });
			}
		}

		for (int j = 0; j < 4; j++) {
			int ny = now.y + ydir[j];
			int nx = now.x + xdir[j];
			if (ny >= H || ny < 0 || nx >= W || nx < 0) continue;
			if (Map[ny][nx] == 1) continue;
			int ncost = dist[now.y][now.x][now.cntK] + 1;
			if (ncost >= dist[ny][nx][now.cntK]) continue;
			dist[ny][nx][now.cntK] = ncost;
			pq.push({ ny, nx, ncost, now.cntK });
		}
	}
	return -1;
}