#include <iostream>
#include <algorithm>
#include <queue>
#define MAX_N 100
using namespace std;
struct Node {
	int y, x, dir, cnt;//cnt == 방향전환 횟수

	bool operator < (Node next) const {
		if (cnt > next.cnt) return true;
		return false;
	}
};
int W, H;
int cntMin[MAX_N][MAX_N];
char Map[MAX_N][MAX_N];
int sy = -1;
int sx, dy, dx;

void input();
int bfs();

int main() {
	input();
	cout << bfs();
	return 0;
}

void input() {
	ios_base::sync_with_stdio(false);
	cin.tie(0);
	cin >> W >> H;
	for (int y = 0; y < H; y++) {
		for (int x = 0; x < W; x++) {
			cin >> Map[y][x];
			if (Map[y][x] == 'C') {
				if (sy == -1) sy = y, sx = x;
				else dy = y, dx = x;
			}
		}
	}
}

int bfs() {
	int ans = 21e8;
	priority_queue<Node>q;
	int ydir[] = { 1,0,-1,0 };
	int xdir[] = { 0,-1,0,1 };
	cntMin[sy][sx] = 0;

	for (int i = 0; i < 4; i++) {//시작하는 방향 4번 다 해보기
		
		for (int y = 0; y < H; y++) {
			for (int x = 0; x < W; x++) {
				cntMin[y][x] = 21e8;
			}
		}

		int ny = sy + ydir[i];
		int nx = sx + xdir[i];
		if (ny >= H || ny < 0 || nx >= W || nx < 0) continue;
		if (Map[ny][nx] == '*') continue;
		q.push({ ny, nx, i, 0 });
		cntMin[ny][nx] = 0;

		while (!q.empty()) {
			Node now = q.top();
			q.pop();

			if (now.cnt > cntMin[now.y][now.x]) continue;
			if (now.y == dy && now.x == dx) {//도착지 발견
				ans = min(ans, now.cnt);
				break;
			}

			for (int j= 0; j < 4; j++) {
				// 현재 방향에서 반대로는 갈 수 없음
				if (j == (now.dir + 2) % 4) continue;
				int ny = now.y + ydir[j];
				int nx = now.x + xdir[j];
				if (ny >= H || nx >= W || ny < 0 || nx < 0) continue;
				if (Map[ny][nx] == '*') continue;
				int ncnt = now.cnt;
				if (j != now.dir) ncnt++;
				if (cntMin[ny][nx] <= ncnt) continue;
				cntMin[ny][nx] = ncnt;
				q.push({ ny,nx,j,ncnt });
			}
		}
	}
	return ans;
}