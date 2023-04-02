#include <iostream>
#include <queue>
#include <algorithm>
#include <vector>
#include <cstring>
using namespace std;
struct Car {
	int y, x;//태운 승객
};
struct cust {
	int sy, sx, dy, dx;
};
int N, M;
int G;// 현재 연료량(입력&출력)
cust Man[410];//idx: 사람이름 / val: 시작&도착 위치
int MAP[22][22];//1,1부터 시작
Car Taxi;
vector<cust>v;
/*
input -> MAP에 승객위치 표시&DAT에 정보 저장

bfs
1. 승객찾기
단계별 flood fill -> 거리 별로 승객 발견할때까지 반복
-> 승객 발견시 v 에 저장 + flag=1
-> flag ==1 이면 다음 단계로 넘어가지 못함

2. 목적지 가기
-> while 문 종료후 sort로 태울 승객 결정
-> 목적지 도착하면 연료= 소모한 연료 2배<-기억해야됨

종료조건
1. 연료 모자란 경우
2. 태울 승객이 없는경우
3. 목적지 도착할 수 없는경우
*/

bool cmp(cust left, cust right) {
	if (left.sy < right.sy) return true;
	if (left.sy > right.sy) return false;
	if (left.sx < right.sx) return true;
	if (left.sx > right.sx) return false;
	return false;
}


// 목적지 도착할 수 없다면  false
bool bfs() {
	//1. 승객 찾기
	queue<Car>q;
	q.push(Taxi);
	int visited[22][22] = { 0, };
	visited[Taxi.y][Taxi.x] = 1;
	int ydir[] = { -1,1,0,0 };
	int xdir[] = { 0,0,-1,1 };

	int flag = 0;
	int dist = 0;
	if (MAP[Taxi.y][Taxi.x] >= 2) {
		v.push_back(Man[MAP[Taxi.y][Taxi.x]]);
		flag = 1;
	}
	while (!q.empty()) {
		int cursize = q.size();
		if (flag == 1) break;//최단거리 발견
		dist++;

		for (int j = 0; j < cursize; j++) {
			Car now = q.front();
			q.pop();

			for (int i = 0; i < 4; i++) {
				int ny = now.y + ydir[i];
				int nx = now.x + xdir[i];
				if (MAP[ny][nx] == 1) continue;
				if (visited[ny][nx] != 0) continue;
				if (MAP[ny][nx] >= 2) {//사람발견
					flag = 1;
					v.push_back(Man[MAP[ny][nx]]);
				}
				visited[ny][nx] = visited[now.y][now.x] + 1;
				q.push({ ny,nx });
			}
		}
	}
	//승객 발견
	G -= dist;//연료 소모
	if (G < 0) return false; //종료조건#1 연료없는 경우
	if (flag == 0) return false;//종료조건#2 태울 승객 없는경우
	sort(v.begin(), v.end(), cmp);

	//2. 목적지 가기
	cust Na = v[0];// 승객 태우기
	//초기화
	MAP[Na.sy][Na.sx] = 0;// 승객 태웠으니 맵에서 지우기
	v.clear();
	queue<Car>().swap(q);
	memset(visited, 0, sizeof(visited));

	q.push({ Na.sy, Na.sx });
	visited[Na.sy][Na.sx] = 1;

	while (!q.empty()) {
		Car now = q.front();
		q.pop();

		//목적지 도착
		if (now.x == Na.dx && now.y == Na.dy) {
			if (G - visited[now.y][now.x] + 1 < 0) {
				return false;//종료조건#1 연료없는 경우
			}
			else {
				G += visited[now.y][now.x] - 1;
				Taxi = { now.y, now.x };
				return true;
			}
		}

		for (int i = 0; i < 4; i++) {
			int ny = now.y + ydir[i];
			int nx = now.x + xdir[i];
			if (MAP[ny][nx] == 1) continue;
			if (visited[ny][nx] != 0) continue;

			visited[ny][nx] = visited[now.y][now.x] + 1;
			q.push({ ny,nx });
		}
	}
	return false;//종료조건#3 목적지 도착할 수 없는경우
}

void solv() {
	for (int i = 0; i < M; i++) {
		bool done = bfs();

		if (done == false) {
			cout << -1;
			return;
		}
	}
	cout << G;
}


void input() {
	ios_base::sync_with_stdio;
	cin.tie(0);

	cin >> N >> M >> G;
	v.reserve(M);
	for (int y = 1; y <= N; y++) {
		for (int x = 1; x <= N; x++) {
			cin >> MAP[y][x];
		}
	}

	cin >> Taxi.y >> Taxi.x;

	for (int i = 0; i < M; i++) {
		cust tmp;
		cin >> tmp.sy >> tmp.sx >> tmp.dy >> tmp.dx;
		MAP[tmp.sy][tmp.sx] = i + 2;//MAP에 사람을 2이상으로 지정
		Man[i + 2] = tmp;// idx: 2 ~ M+1
	}
}

void reset() {
	for (int y = 0; y < 22; y++) {
		for (int x = 0; x < 22; x++) {
			MAP[y][x] = 1;// 벽 둘러싸기
		}
	}
}

int main() {
	reset();
	input();
	solv();
	return 0;
}