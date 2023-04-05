#include <iostream>
#include <vector>
using namespace std;
struct Fire {
	int r, c, m, s, d;
};
int N, M, K;
vector<Fire>ball;// idx : 파이어볼 이름, value : 파이어볼 정보
vector<Fire>temp;
vector<int>MAP[50][50];//파이어볼의 이름만 저장한다

/*
sol() => 모든 파이어볼 이동을 K번 반복한다
		=> K번 반복되지 않더라도, 남은 파이어볼의 수가 1개 이하이면 종료시킨다

Move() => 파이어볼을 정보에 따라 이동시킨다.
				장애물이 없기때문에 bfs 할 필요 없다
				Map 에 좌표를 저장한다

				 nr = (N*1000 + Now.r + ydir[Now.d] * Now.s) % N
				 주의!! -> 속도 ~ 1000 && ydir[] == -1 인경우, 음의 index에 접근 할 수 있음
				 N*1000 더해서 보정해주기!

Process() => MAP에 2개이상의 파이어볼 이 있을때 처리한다

massSum() => K번 반복후, 남은 fireball의 질량 합을  return한다

*/

void input();
void sol();
void Move();
void Process();
int massSum();


int main() {
	input();
	sol();
	cout << massSum();
	return 0;
}

void input() {
	ios_base::sync_with_stdio(false);
	cin.tie(0);
	cin >> N >> M >> K;
	ball.reserve(N * N);
	for (int i = 0; i < M; i++) {
		int r, c, m, s, d;
		cin >> r >> c >> m >> s >> d;
		ball.push_back({ r - 1,c - 1,m,s,d });
	}
}

void sol() {
	while (K--) {
		if (ball.size() <= 1) break;
		Move();
		Process();
	}
}

void Move() {
	int ydir[] = { -1, -1, 0, 1, 1, 1,0, -1 };
	int xdir[] = { 0 , 1, 1, 1, 0, -1,-1,-1 };
	int size = ball.size();
	for (int i = 0; i < size; i++) {
		Fire Now = ball[i];
		int nr = (N * 1000 + Now.r + ydir[Now.d] * Now.s) % N;//Now.s가 큰값이면 음수 나올 수 있음
		int nc = (N * 1000 + Now.c + xdir[Now.d] * Now.s) % N;
		ball[i].r = nr;//다음위치로 이동
		ball[i].c = nc;
		MAP[nr][nc].push_back(i);//MAP에 이름 저장
	}
}


void Process() {
	vector<Fire>().swap(temp);//새로운 fireball  temp에 저장
	temp.reserve(N * N);//4ms 절약
	for (int y = 0; y < N; y++) {
		for (int x = 0; x < N; x++) {

			int size = MAP[y][x].size();
			if (size > 1) {//2개 이상 저장시
				int mass = 0;
				int speed = 0;
				int flagD = 0;//방향체크 용
				int tmpDir = ball[MAP[y][x][0]].d % 2;
				for (int i = 0; i < size; i++) {
					mass += ball[MAP[y][x][i]].m;
					speed += ball[MAP[y][x][i]].s;
					if (tmpDir != ball[MAP[y][x][i]].d % 2) {//방향 홀짝 다르면
						flagD = 1;
					}
				}
				//질량, 속력 구하기
				mass /= 5;
				speed /= size;

				//#3 합치기
				if (mass == 0) continue;//질량 0이면 삭제
				if (flagD == 0) {//모두 방향 홀짝 같으면
					for (int j = 0; j < 8; j += 2) {
						temp.push_back({ y,x,mass,speed,j });
					}
				}
				else {
					for (int j = 1; j < 8; j += 2) {
						temp.push_back({ y,x,mass,speed,j });
					}
				}
			}
			else if (size == 1) {//1개 저장시
				temp.push_back(ball[MAP[y][x][0]]);
			}
		}
	}
	temp.swap(ball);//ball에 temp 대입 
	for (int y = 0; y < N; y++) {
		for (int x = 0; x < N; x++) {
			MAP[y][x].clear();
		}
	}
}

int massSum() {
	int ans = 0;
	int size = ball.size();
	for (int i = 0; i < size; i++) {
		ans += ball[i].m;
	}
	return ans;
}
