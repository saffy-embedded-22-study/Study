#include <iostream>
#include <queue>
using namespace std;

struct Node {
	int y, x, turn;
};
int N, M; //메모리 2068kb 시간 0ms
char Map[100][100]; 
int Mir[100][100]; //거울 수 + 1
int dir[4][2] = { -1,0,1,0,0,-1,0,1 };

int main() {
	cin >> M >> N;
	int sy, sx;
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < M; j++) {
			char a; cin >> a;
			Map[i][j] = a;
			if (a == 'C') { //둘중 아무 C에서나 시작
				sy = i;
				sx = j;
			}
		}
	}
	queue<Node> q;
	q.push({ sy,sx,0 });
	Mir[sy][sx] = 1; //시작점

	while (!q.empty()) {
		Node now = q.front();
		q.pop();
		for (int i = 0; i < 4; i++) {
			int ny = now.y;
			int nx = now.x;
			while (1) {
				ny += dir[i][0];
				nx += dir[i][1];
				if (ny < 0 || nx < 0 || ny >= N || nx >= M) break;
				if (Map[ny][nx] == '*') break;
				if (Mir[ny][nx] == 0) { //1차 방문했을 때 값으로 저장
					if (Map[ny][nx] == 'C') { //도착
						cout << now.turn; 
						return 0;
					}
					Mir[ny][nx] = now.turn + 1;
					q.push({ ny,nx,now.turn + 1 });
				}
			}
		}
	}
	return 0;
}
