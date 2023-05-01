#include <iostream>
#include <queue>
using namespace std;

struct Node {
	int y, x, n;
};
int N; //2032kb 0ms
char Map[50][51]; //갈 수 있는 게 '1' 막힌 게 '0'
int visit[50][50]; //n칸 지우고 갈 수 있으면 n + 1
int dir[4][2] = { -1,0,1,0,0,-1,0,1 };

void Run(); //dfs

int main() {
	cin >> N;
	for (int i = 0; i < N; i++) cin >> Map[i];
	Run();
	cout << visit[N - 1][N - 1] - 1;
	return 0;
}
void Run() {
	queue<Node> q;
	q.push({ 0,0,1 });
	visit[0][0] = 1;
	while (!q.empty()) {
		Node now = q.front();
		q.pop();
		for (int i = 0; i < 4; i++) {
			int ny = now.y + dir[i][0];
			int nx = now.x + dir[i][1];
			if (ny < 0 || nx < 0 || ny >= N || nx >= N) continue;

			int nn = now.n + '1' - Map[ny][nx];
			if (visit[ny][nx] != 0 && nn >= visit[ny][nx]) continue; //같거나 적게 지우고 왔던 곳 안감

			visit[ny][nx] = nn;
			q.push({ ny,nx,nn });
		}
	}
}