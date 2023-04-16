#include <iostream>
#include <cstring>
#include <queue>
#include <vector>
using namespace std;

int N, Q;
int M;
int ice;
int A[65][65];
int Save[65][65];
int dir[4][2] = { -1,0,1,0,0,-1,0,1 };
struct Node {
	int y;
	int x;
};

//메모리 2056 kb | 시간 44 ms

void Magic(int L); //마법 시전
void Tornado(int L); 
void Turn(int sy, int sx, int S); //격자 시작점 sy, sx에서 S크기 만큼 회전
void Fire(); 
int MaxIce(); //제일 큰 얼음 찾기
int Fill(int y, int x);

int main() {
	cin >> N >> Q;
	M = 1;
	for (int i = 0; i < N; i++) M *= 2;
	for (int i = 0; i < M; i++) {
		for (int j = 0; j < M; j++) {
			int a;  cin >> a;
			A[i][j] = a;
			ice += a;
		}
	}
	for (int i = 0; i < Q; i++) {
		int a; cin >> a;
		Magic(a);
	}
	cout << ice << endl;
	cout << MaxIce();
	return 0;
}
void Magic(int L) {
	Tornado(L);
	Fire();
}
void Tornado(int L) {
	if (L == 0) return;

	int S = 1;
	for (int i = 0; i < L; i++) S *= 2;

	memset(Save, 0, sizeof(Save));
	for (int i = 0; i < M; i++) {
		for (int j = 0; j < M; j++) {
			Save[i][j] = A[i][j];
		}
	}
	for (int i = 0; i < M; i += S) {
		for (int j = 0; j < M; j += S) {
			Turn(i, j, S);
		}
	}
}
void Turn(int sy, int sx, int S) {
	for (int i = 0; i < S; i++) {
		for (int j = 0; j < S; j++) {
			A[sy + i][sx + j] = Save[sy + S - 1 - j][sx + i];
		}
	}
}
void Fire() {
	vector<Node> v;
	for (int y = 0; y < M; y++) {
		for (int x = 0; x < M; x++) {
			if (A[y][x] == 0) continue;
			int cnt = 0;
			for (int i = 0; i < 4; i++) {
				int ny = y + dir[i][0];
				int nx = x + dir[i][1];
				if (ny < 0 || nx < 0 || ny >= M || nx >= M) continue;
				if (A[ny][nx] == 0) continue;
				cnt++;
			}
			if (cnt < 3) {
				v.push_back({ y,x }); //녹을 위치 넣어주고
			}
		}
	}
	int n = v.size();
	for (int i = 0; i < n; i++) {
		Node now = v[i];
		A[now.y][now.x]--; //녹이기
		ice--;
	}

}
int MaxIce() {
	int Max = 0;
	for (int i = 0; i < M; i++) {
		for (int j = 0; j < M; j++) {
			if (A[i][j] == 0) continue; 
			int res = Fill(i, j);
			if (Max < res) Max = res;
		}
	}
	return Max;
}
int Fill(int y, int x) {
	queue<Node>q;
	q.push({ y,x });
	A[y][x] = 0; //방문한 곳은 없애버림
	int cnt = 1;
	while (!q.empty()) {
		Node now = q.front();
		q.pop();
		for (int i = 0; i < 4; i++) {
			int ny = now.y + dir[i][0];
			int nx = now.x + dir[i][1];
			if (ny < 0 || nx < 0 || ny >= M || nx >= M) continue;
			if (A[ny][nx] == 0) continue;
			q.push({ ny,nx });
			A[ny][nx] = 0;
			cnt++;
		}
	}
	return cnt;
}
