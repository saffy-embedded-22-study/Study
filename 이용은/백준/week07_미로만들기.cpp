#include <iostream>
#include <queue>
#define MAX_N 50
#define INF 21e8
using namespace std;
struct Node {
	int y, x, cost;
	
	bool operator < (Node next) const {
		return cost > next.cost;
	}
};
int N;
string MAP[MAX_N];
int minCost[MAX_N][MAX_N];


void init();
int Dijkstra();


int main() {
	init();
	cout <<Dijkstra();
	return 0;
}


void init() {
	ios_base::sync_with_stdio(false);
	cin.tie(0);
	cin >> N;
	for (int y = 0; y < N; y++) cin >> MAP[y];
}

int Dijkstra() {
	priority_queue<Node>pq;
	pq.push({ 0,0,0 });

	for (int y = 0; y < N; y++)
		for (int x = 0; x < N; x++)
			minCost[y][x] = INF;
	minCost[0][0] = 0;

	int ydir[] = { 1,-1,0,0 };
	int xdir[] = { 0,0,1,-1 };

	while (!pq.empty()) {
		Node now = pq.top();
		pq.pop();
		
		if (now.cost > minCost[now.y][now.x]) continue;
		//확정
		if (now.y == N - 1 && now.x == N - 1) return now.cost;

		for (int i = 0; i < 4; i++) {
			int ny = now.y + ydir[i];
			int nx = now.x + xdir[i];
			if (ny >= N || ny < 0 || nx >= N || nx < 0) continue;
			int ncost = now.cost;
			if (MAP[ny][nx] == '0') ncost++;
			if (ncost >= minCost[ny][nx]) continue;
			minCost[ny][nx] = ncost;
			pq.push({ ny,nx,ncost });
		}
	}
	return -1;
}