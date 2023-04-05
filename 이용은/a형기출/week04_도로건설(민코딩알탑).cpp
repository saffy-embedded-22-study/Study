#include <iostream>
#include <algorithm>
#include <queue>
using namespace std;
int N, M;
int MAP[1000][1000];
int dist[1000][1000];
struct Node {
	int y, x, cost;
	bool operator <(Node next)const {
		if (cost < next.cost) return false;
		if (cost > next.cost) return true;
		return false;
	}
};


void input();
int Dijstra();

int main() {
	input();
	cout <<Dijstra();
	return 0;
}

void input() {
	cin >> N >> M;
	for (int y = 0; y < N; y++) {
		for (int x = 0; x < M; x++) {
			cin >> MAP[y][x];
		}
	}
	for (int i = 0; i < N; i++) {
		fill(dist[i], dist[i] + M, 21e8);
	}
}

int Dijstra() {
	priority_queue<Node>pq;
	pq.push({ 0,0,MAP[0][0] });
	
	dist[0][0] = MAP[0][0];

	int ydir[] = { -1,1,0,0 };
	int xdir[] = { 0,0,-1,1 };

	while (!pq.empty()) {
		Node now = pq.top();
		pq.pop();

		if (now.cost > dist[now.y][now.x]) continue;
		if (now.y == N - 1 && now.x == M - 1) return now.cost;

		for (int i = 0; i < 4; i++) {
			int ny = now.y + ydir[i];
			int nx = now.x + xdir[i];
			if (ny >= N || nx >= M || ny < 0 || nx < 0) continue;
			if (MAP[ny][nx] == -1) continue;
			int ncost = dist[now.y][now.x] + MAP[ny][nx];
			if (ncost >= dist[ny][nx]) continue;
			dist[ny][nx] = ncost;
			pq.push({ ny,nx,ncost });
		}
	}

	return -1;
}