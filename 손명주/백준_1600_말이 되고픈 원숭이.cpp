#include <iostream>
#include <queue>
using namespace std;

int K;
int W, H;//가로 세로
int Map[200][200];//0평지 1장애물
int visited[200][200][31];//말점프 x번으로
int ydir[12] = { -1,1,0,0,-1,-2,-2,-1,1,2,2,1 };
int xdir[12] = { 0,0,-1,1,-2,-1,1,2,2,1,-1,-2 };
struct Node {
	int y, x, move, jump;
};

int Bfs() {
	queue<Node> q;
	q.push({ 0,0,1,0 });
	visited[0][0][0] = 1;
	int ans = 10000000;

	while (!q.empty()) {
		Node now = q.front();
		q.pop();

		if (now.y == H - 1 && now.x == W - 1) {
			if (ans > now.move - 1) ans = now.move - 1;
		}
		
		for (int i = 0; i < 12; i++) {
			if (now.jump == K && i >= 4) break;
			int move = now.move + 1;
			int jump = now.jump + (i >= 4);

			int ny = now.y + ydir[i];
			int nx = now.x + xdir[i];
			if (ny < 0 || nx < 0 || ny >= H || nx >= W) continue;
			if (Map[ny][nx] == 1) continue;
			if (visited[ny][nx][jump] != 0 && visited[ny][nx][jump] <= move) continue;//더 적게 가봤으면 x
			visited[ny][nx][jump] = move;
			q.push({ ny,nx,move,jump });
		}

	}
	if (ans == 10000000) ans = -1;
	return ans;
}

int main() {
	cin >> K >> W >> H;
	for (int i = 0; i < H; i++) {
		for (int j = 0; j < W; j++) {
			cin >> Map[i][j];
		}
	}
	cout << Bfs();
	return 0;
}