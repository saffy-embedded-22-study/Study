#include <iostream>
#include <cstring>
#include <vector>
using namespace std;

struct Shark {
	int y, x, s, d, z, alive;
};
vector<Shark> v;
int R, C, M;
int Map[100][100];
int Temp[100][100];
int Caught;
int dir[4][2] = { -1,0,1,0,0,1,0,-1 };

//메모리 2688kb | 시간 24ms

void Catch(int); //i열 고기잡기
void Move(); //상어 움직이기

int main() {
	cin >> R >> C >> M;
	memset(Map, -1, sizeof(Map));
	for (int i = 0; i < M; i++) {
		int y, x, s, d, z; 
		cin >> y >> x >> s >> d >> z; y--; x--; d--;

		if (d < 2) s %= 2 * (R - 1);
		else s %= 2 * (C - 1);

		v.push_back({ y,x,s,d,z,1 });
		Map[y][x] = i;
	}
	for (int i = 0; i < C - 1; i++) {
		Catch(i);
		Move();
	}
	Catch(C - 1);
	cout << Caught;
	return 0;
}
void Catch(int c) {
	for (int i = 0; i < R; i++) {
		int now = Map[i][c];
		if (now != -1) {
			Caught += v[now].z;
			v[now].alive = 0;
			return;
		}
	}
}
void Move() {
	memset(Temp, -1, sizeof(Temp));
	for (int i = 0; i < M; i++) {
		Shark now = v[i];
		if (now.alive == 0) continue;
		
		int ny = now.y + now.s * dir[now.d][0] + 2 * (R - 1); //위에서 s를 0 ~ 2*(R-1)-1 로 제한해서 3가지 경우가 있음
		int nx = now.x + now.s * dir[now.d][1] + 2 * (C - 1); //(1)그냥 움직여도 범위안 (2) 한번 방향 전환 (3) 두번 방향 전환
		ny %= 2 * (R - 1); // (3) 처리
		nx %= 2 * (C - 1);

		if (ny < 0 || nx < 0 || ny >= R || nx >= C) { // (2) 처리
			if (now.d < 2) { //상하
				ny = 2 * (R - 1) - ny;
				v[i].d = (now.d + 1) % 2;
			}
			else { //좌우
				nx = 2 * (C - 1) - nx;
				v[i].d = (now.d + 1) % 2 + 2;
			}
		}
		v[i].y = ny;
		v[i].x = nx;

		if (Temp[ny][nx] != -1) { //먼저온 상어가 있음
			int ind = Temp[ny][nx];
			if (v[ind].z < now.z) {
				v[ind].alive = 0;
				Temp[ny][nx] = i;
			}
			else
				v[i].alive = 0;
		}
		else Temp[ny][nx] = i;
	}
	memcpy(Map, Temp, sizeof(Map));
}