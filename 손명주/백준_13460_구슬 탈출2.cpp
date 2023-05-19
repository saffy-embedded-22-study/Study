#include <iostream>
#include <queue>
using namespace std;

int N, M; // 2024kb 0ms
char Map[10][11];
int dir[4][2] = { -1,0,0,-1,1,0,0,1 }; //상 좌 하 우 순서

struct Ball {
	int y, x, hole; //구멍에 들어갔으면 hole = 1
};
struct State {
	Ball r, b;
	int d;
	int turn;
};
queue<State> q;

int Solve();
Ball Move(Ball, int); //Ball을 int방향으로 이동

int main() {
	cin >> N >> M;
	Ball red, blue;
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < M; j++) {
			char now; cin >> now;
			Map[i][j] = now;
			if (now == 'R') red = { i,j,0 };
			if (now == 'B') blue = { i,j,0 };
		}
	}
	q.push({ red,blue,-1,0 });
	cout << Solve();
	return 0;
}

int Solve() {
	int cnt = 1;
	while (!q.empty()) {
		State now = q.front();
		q.pop();
		if (now.turn == 10) return -1;
		for (int i = 0; i < 4; i++) { //i방향으로 떨어지는 게 i
			if (i % 2 == now.d % 2) continue; //ex 상 방향으로 온경우 상하 안감 (상 = 지금 / 하 = 기울이기 전)
			if (Map[now.r.y + dir[i][0]][now.r.x + dir[i][1]] == '#' && Map[now.b.y + dir[i][0]][now.b.x + dir[i][1]] == '#') continue; //가도 똑같으면 안감

			Map[now.r.y][now.r.x] = 'R'; //지금 공들 위치
			Map[now.b.y][now.b.x] = 'B';

			bool order = true;
			int ry = now.r.y;
			int rx = now.r.x;
			while (1) {
				ry += dir[i][0];
				rx += dir[i][1];
				if (Map[ry][rx] == 'B') order = false; //파란공이 진로에 있으면 파란거 먼저
				if (Map[ry][rx] != '.') break;
			}

			Ball nr, nb;
			if (order) {
				nr = Move(now.r, i);
				nb = Move(now.b, i);
			}
			else {
				nb = Move(now.b, i);
				nr = Move(now.r, i);
			}

			if (nr.hole == 1 && nb.hole == 0) return now.turn + 1; //빨간공만 들어갔을 때 정답

			Map[nr.y][nr.x] = '.'; //공 지워줌
			Map[nb.y][nb.x] = '.';

			if (nr.hole == 0 && nb.hole == 0) q.push({ nr,nb,i,now.turn + 1 }); //두공다 살아있는 경우만 계속함
		}
	}
	return -1;
}
Ball Move(Ball ball, int d) {
	int ny = ball.y;
	int nx = ball.x;
	Map[ny][nx] = '.';
	while (1) {
		ny += dir[d][0];
		nx += dir[d][1];
		if (Map[ny][nx] != '.') {
			if (Map[ny][nx] == 'O') return { ny -= dir[d][0],nx -= dir[d][1],1 };

			ny -= dir[d][0];
			nx -= dir[d][1];
			Map[ny][nx] = 'b';
			return { ny,nx,0 };
		}
	}
}