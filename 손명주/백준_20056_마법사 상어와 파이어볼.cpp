#include <iostream>
#include <vector>
using namespace std;

//테케는 맞는데 내면 바로 틀려여...
int N, M, K;
int Map[60][60];
int Dir[8][2] = { -1,0,-1,1,0,1,1,1,1,0,1,-1,0,-1,-1,-1 };
struct Fire {
	int y, x;
	int mass, speed, dir;
};
int Mass; //총합
vector<Fire> v;

void Move();
void Event();
void Solve();

int main() {
	cin >> N >> M >> K;
	for (int i = 1; i <= M; i++) {
		int r, c, m, s, d;
		cin >> r >> c >> m >> s >> d; r--; c--;

		v.push_back({ r,c,m,s,d });
		Map[r][c] = 1;
		Mass += m;
	}
	Solve();
	cout << Mass;
	return 0;
}
void Solve() {
	for (int i = 1; i <= K; i++) {
		if (Mass == 0) return;
		Move();
		Event();
	}
}
void Move() { //살아있는애들 움직이기
	int num = v.size();

	for (int i = 0; i < num; i++) {
		Fire now = v[i];
		if (now.mass == 0) continue;
		int ny = now.y + now.speed * Dir[now.dir][0];
		int nx = now.x + now.speed * Dir[now.dir][1];
		ny = (ny + 300 * N) % N;
		nx = (nx + 300 * N) % N;

		Map[now.y][now.x]--;
		Map[ny][nx]++;
		v[i].y = ny;
		v[i].x = nx;
	}
}
void Event() {
	int num = v.size();
	for (int i = 0; i < num; i++) {
		Fire now = v[i];
		if (now.mass == 0) continue;
		if (Map[now.y][now.x] == 1) continue; //여러개 있는 경우만 

		int tMass = 0; //이 장소에 있는 mass 합
		int tSpeed = 0; //speed 합
		int tn = 0; //파이어볼 수
		int flag = now.dir % 2;

		for (int j = i; j < num; j++) {
			Fire here = v[j];
			if (here.y != now.y || here.x != now.x) continue;
			if (here.mass == 0) continue;

			tMass += here.mass;
			tSpeed += here.speed;
			tn++;
			if (here.dir % 2 != flag) flag = -1;

			Mass -= here.mass;
			v[j].mass = 0;//모인거 다죽임
		}

		//파이어볼 만들기
		int mass = tMass / 5;
		int speed = tSpeed / tn;
		int d = 0;
		if (flag == -1) d = 1;

		if (mass == 0) continue;
		Mass += mass * 4;
		Map[now.y][now.x] = 4;
		for (int j = 0; j < 4; j++) {
			v.push_back({ now.y, now.x, mass, speed, d + 2 * j });
		}
	}
}