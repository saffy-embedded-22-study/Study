#include <iostream>
#include <algorithm>
#include <cstring>
#include <vector>
#include <queue>
using namespace std;

struct Passenger {
	int n; //승객 번호 0 부터
	int y;
	int x;
	int gy;
	int gx;
	int fromP; //손님에서 목적지까지 거리 :고정
	int toP; //현재 택시 위치에서 손님까지 거리 :변화
};
bool cmp(Passenger left, Passenger right) {
	if (left.toP < right.toP) return true;
	if (left.toP > right.toP) return false;
	if (left.y < right.y) return true;
	if (left.y > right.y) return false;
	if (left.x < right.x) return true;
	if (left.x > right.x) return false;
	return false;
}
struct node {
	int y, x;
};
int N, M, fuel;
int MAP[20][20];
int visit[20][20];
int dir[4][2] = { -1,0,1,0,0,-1,0,1 };
int Y, X;//택시 위치
vector<Passenger> v; //손님
int done[400]; //승객 번호


//손님 별로 목적지까지 거리 구하는 용 손님 넣을 때 한번씩
int Dist(int y, int x, int gy, int gx) {
	if (y == gy && x == gx) return 0;
	memset(visit, 0, sizeof(visit));
	queue<node> q;
	q.push({ y, x });
	visit[y][x] = 1;
	while (!q.empty()) {
		node now = q.front();
		q.pop();
		for (int i = 0; i < 4; i++) {
			int ny = now.y + dir[i][0];
			int nx = now.x + dir[i][1];
			if (ny < 0 || nx < 0 || ny >= N || nx >= N) continue;
			if (visit[ny][nx] >= 1) continue;
			if (MAP[ny][nx] == 1) continue;
			if (ny == gy && nx == gx) return visit[now.y][now.x];
			visit[ny][nx] = visit[now.y][now.x] + 1;
			q.push({ ny,nx });
		}
	}
	return -1;
}

//이거는 택시 위치에서 부터 플러드필 한번
//-> 택시에서의 거리 visit에 써짐
void Fill(int y, int x) {
	memset(visit, 0, sizeof(visit));
	queue<node> q;
	q.push({ y, x });
	visit[y][x] = 1;
	while (!q.empty()) {
		node now = q.front();
		q.pop();
		for (int i = 0; i < 4; i++) {
			int ny = now.y + dir[i][0];
			int nx = now.x + dir[i][1];
			if (ny < 0 || nx < 0 || ny >= N || nx >= N) continue;
			if (visit[ny][nx] >= 1) continue;
			if (MAP[ny][nx] == 1) continue;
			visit[ny][nx] = visit[now.y][now.x] + 1;
			q.push({ ny,nx });
		}
	}
	return;
}

//손님 찾아서 이동
int Move() {
	int left = M;
	while (1) {
		Fill(Y, X); //visit에 거리 저장됨

		for (int i = 0; i < M; i++) {
			Passenger now = v[i];
			int toNow = visit[now.y][now.x] - 1;

			if (toNow < 0) return -1; //손님까지 못가는 손님이 있을 때 영업안함 (벽이 있다든가 할까봐)
			v[i].toP = toNow;
		}

		sort(v.begin(), v.end(), cmp); //이미 태워다 준 손님도 정렬됨

		for (int i = 0; i < M; i++) {
			Passenger now = v[i];
			if (done[now.n] == 1) continue;

			if (now.fromP == -1) return -1; //목적지까지 못가는 손님 (벽이 있다든가 할까봐)
			done[now.n] = 1;
			left--;

			if (fuel < now.toP) return -1; //기름없어서 손님까지 못감
			fuel -= now.toP;
			if (fuel < now.fromP) return -1; //기름없어서 도착지까지 못감

			//도착
			Y = now.gy;
			X = now.gx;
			fuel += now.fromP;
			if (left == 0) return fuel;
			break; //한번에 한명만
		}
	}
	
}

int main() {
	cin >> N >> M >> fuel;
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			cin >> MAP[i][j];
		}
	}
	cin >> Y >> X;
	Y--; X--;

	for (int i = 0; i < M; i++) {
		int a, b, c, d;
		cin >> a >> b >> c >> d;
		v.push_back({ i,a - 1, b - 1, c - 1, d - 1,Dist(a - 1,b - 1,c - 1,d - 1),0 }); //키우기 싫어서 이랬습니다
	}
	cout << Move();

	return 0;
}