#include <iostream>
#include <algorithm>
#include <cmath>
#include <cstring>
#include <queue>
using namespace std;
int N, Q;

int A [64][64];
int Acopy[64][64];
int iceSum;//얼음 총합, 입력받을때구하고, 찾으면서 하나씩 빼주기

void input();
void sol();
void rotateMap(int L);//시계방향 90도 회전
void meltingIce();// 얼음 줄이기
int findAns();//칸수 제일 큰 섬찾기
int bfs(int , int);

int main() {
	input();
	sol();
	cout << iceSum << '\n';
	cout << findAns();
	return 0;
}

void input() {
	ios_base::sync_with_stdio(false);
	cin.tie(0);

	cin >> N >> Q;
	int size = pow(2, N);
	for (int y = 0; y < size; y++) {
		for (int x = 0; x < size; x++) {
			cin >> A[y][x];
			iceSum += A[y][x];
		}
	}
}
void sol() {
	for (int i = 0; i < Q; i++) {
		int query;
		cin >> query;
		rotateMap(query);
		meltingIce();
	}
}
void rotateMap(int L) {
	if (L== 0) return;
	int rotateCnt = pow(4, N - L);
	int forCnt = pow(2, L);
	for (int k = 0; k < rotateCnt; k++) {
		int sy = forCnt*((forCnt * k) / (int)pow(2, N));//격자 시작위치
		int sx = (forCnt * k) % (int)pow(2, N);
		for (int y = 0; y < forCnt; y++) {
			for (int x = 0; x <forCnt; x++) {
				int ny = sy +x;
				int nx = sx + (forCnt - 1 - y);
				Acopy[ny][nx] = A[sy + y][sx + x];
			}
		}
	}
	memcpy(A, Acopy, sizeof(Acopy));
}
void meltingIce() {
	memcpy(Acopy, A, sizeof(Acopy));
	int size = pow(2, N);
	int ydir[] = { -1,1,0,0 };
	int xdir[] = { 0,0,-1,1 };
	for (int y = 0; y < size; y++) {
		for (int x = 0; x < size; x++) {
			//상하좌우 탐색
			int cnt = 0;
			for (int i = 0; i < 4; i++) {
				int ny = y + ydir[i];
				int nx = x + xdir[i];
				if (ny >= size || nx >= size || nx < 0 || ny < 0) continue;
				if (A[ny][nx] == 0) continue;
				cnt++;
			}
			//2개 이하인 경우, -=1;
			if (cnt <= 2 && A[y][x] != 0) {
				Acopy[y][x] -= 1;
				iceSum -= 1;
			}
		}
	}
	memcpy(A, Acopy, sizeof(Acopy));
}
int findAns() {
	if (iceSum == 0) return 0;
	int ans = 0;
	int size = pow(2, N);
	memset(Acopy, 0, sizeof(Acopy));//Acopy를 visited로 사용
	//섬찾기
	for (int y = 0; y < size; y++) {
		for (int x = 0; x < size; x++) {
			if (A[y][x] == 0) continue;
			if (Acopy[y][x] == 1) continue;
			ans = max(ans,bfs(y, x));
		}
	}
	return ans;
}

int bfs(int startY, int startX) {
	struct Node {
		int y, x;
	};
	queue<Node>q;
	q.push({ startY,startX });
	Acopy[startY][startX] = 1;

	int ydir[] = { -1,1,0,0 };
	int xdir[] = { 0,0,-1,1 };

	int size = pow(2, N);
	int iceCnt = 1;//섬의 칸수
	while (!q.empty()) {
		Node now = q.front();
		q.pop();

		for (int i = 0; i < 4; i++) {
			int ny = now.y + ydir[i];
			int nx = now.x + xdir[i];
			if (ny >= size || nx >= size || ny < 0 || nx < 0)continue;
			if (Acopy[ny][nx] == 1) continue;
			if (A[ny][nx] == 0) continue;
			Acopy[ny][nx] = 1;
			iceCnt++;
			q.push({ ny,nx });
		}
	}

	return iceCnt;
}
