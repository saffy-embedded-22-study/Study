#include <iostream>
#include <algorithm>
#define INF 21e8
using namespace std;
int N, M;
int Ry, Rx;//빨간구슬 위치
int By, Bx;//파란구슬 위치
char Map[10][10];
int ydir[] = { -1,1,0,0 };
int xdir[] = { 0,0,-1,1 };
int ans = INF;

void init();
void dfs(int, int);
bool Move(int);

int main() {
	init();
	int Rx1 = Rx;//복구용
	int Ry1 = Ry;
	int By1 = By;
	int Bx1 = Bx;
	for (int i = 0; i < 4; i++) {
		if (Move(i)) {//구슬 둘중 하나라도 움직일 수 있을때만
			dfs(1, i);
			//복구
			Rx = Rx1;
			Ry = Ry1;
			By = By1;
			Bx = Bx1;
		}
	}
	if (ans == INF) cout << -1;
	else cout << ans;
}

void init() {
	ios_base::sync_with_stdio(false);
	cin.tie(0);
	cin >> N >> M;
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < M; j++) {
			char temp;
			cin >> temp;
			if (temp == 'R') Ry = i, Rx = j,temp='.';//Map에서 R,B지우기
			else if (temp == 'B') By = i, Bx = j, temp = '.';
			Map[i][j] = temp;
		}
	}
}

void dfs(int depth, int dir) {
	//base
	if (depth >= ans) return;//최소값이상인경우 
	if (depth == 11) return;//11회 이상인경우
	if (Bx == -1) return;//파란색 들어가는경우
	if (Rx == -1) {//정답
		ans = min(ans, depth);
		return;
	}
	//recursive
	
	int backupRy = Ry;
	int backupRx = Rx;
	int backupBy = By;
	int backupBx = Bx;

	for (int i = 0; i < 4; i++) {
		if (i == dir) continue;//같은방향 가지치기
		if (Move(i)) {//구슬 둘중 하나라도 움직일 수 있을때만
			dfs(depth + 1, i);
			Ry = backupRy;
			Rx = backupRx;
			By = backupBy;
			Bx = backupBx;
		}
	}

}


bool Move(int dir) {
	//빨간구슬 이동
	int cntR = 0;//두개의 구슬이 같은위치일때, 순서 처리용
	int Rny = Ry;
	int Rnx = Rx;
	while (true) {
		Rny += ydir[dir];
		Rnx += xdir[dir];
		cntR++;
		if (Map[Rny][Rnx] == '#') {
			Rny -= ydir[dir];
			Rnx -= xdir[dir];
			cntR--;
			break;
		}

		else if (Map[Rny][Rnx] == 'O') {
			Rnx = -1, Rny = -1;//구슬이 빠지면 -1,-1로 변경
			break;
		}
	}
	//파란구슬 이동
	int Bny = By;
	int Bnx = Bx;
	int cntB = 0;
	while (true) {
		Bny += ydir[dir];
		Bnx += xdir[dir];
		cntB++;
		if (Map[Bny][Bnx] == '#') {
			Bny -= ydir[dir];
			Bnx -= xdir[dir];
			cntB--;
			break;
		}
		else if (Map[Bny][Bnx] == 'O') {
			Bnx = -1, Bny = -1;//구슬이 빠지면 -1,-1로 변경
			break;
		}
	}
	//같은위치 처리 -> 이동횟수가 적은 쪽이 벽에 붙어있어야함!
	if (Rnx !=-1 && Rny == Bny && Rnx == Bnx ) {//같은위치인경우(구멍에 빠진경우는 제외)
		if (cntR < cntB) {
			Bny -= ydir[dir];
			Bnx -= xdir[dir];
		}
		else {
			Rny -= ydir[dir];
			Rnx -= xdir[dir];
		}
	}
	Ry = Rny, Rx = Rnx;
	By = Bny, Bx = Bnx;
	
	return !(cntB == 0 && cntR == 0);//좌표 둘다 바뀌지 않은경우 -> false
}