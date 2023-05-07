#include <iostream>
using namespace std;

int N, M;
int Map[500][500];
int Way[500][500];
int dir[4][2] = { -1,0,1,0,0,-1,0,1 };

int Down(int, int); //int int 에서 아래로만

int main() {
	cin >> N >> M;
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < M; j++) {
			cin >> Map[i][j];
			Way[i][j] = -1;
		}
	}
	Way[N - 1][M - 1] = 1;
	cout << Down(0, 0);
	return 0;
}
int Down(int y, int x) {
	if (Way[y][x] != -1) return Way[y][x];

	int here = 0;
	for (int i = 0; i < 4; i++) {
		int ny = y + dir[i][0];
		int nx = x + dir[i][1];
		if (ny < 0 || nx < 0 || ny >= N || nx >= M) continue;
		if (Map[ny][nx] >= Map[y][x]) continue;

		here += Down(ny, nx);
	}
	return Way[y][x] = here;
}