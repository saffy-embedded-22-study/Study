#include <iostream>
#include <cstring>
#include <queue>
using namespace std;

int N, M;
int Cost[1000][1000]; //입력값
int Min[1000][1000]; //위치별 최소 비용 저장
int dir[4][2] = { -1,0,1,0,0,-1,0,1 };
struct Node {
	int y;
	int x;
	int c;
};
struct cmp {
	bool operator()(Node left, Node right) {
		if (left.c > right.c) return true;
		if (left.c < right.c) return false;
		if (left.x < right.x) return true;
		if (left.x > right.x) return false;
		if (left.y < right.y) return true;
		if (left.y > right.y) return false;
		return false;
	}
};
void Run() {
	priority_queue<Node,vector<Node>,cmp> q;
	q.push({ 0, 0, Cost[0][0] });
	Min[0][0] = Cost[0][0];
	while (!q.empty()) {
		Node now = q.top();
		q.pop();

		for (int i = 0; i < 4; i++) {
			int ny = now.y + dir[i][0];
			int nx = now.x + dir[i][1];
			if (ny < 0 || nx < 0 || ny >= N || nx >= M) continue;
			if (Cost[ny][nx] == -1) continue;
			int cost = now.c + Cost[ny][nx];
			if (Min[ny][nx] >= 0 && Min[ny][nx] <= cost) continue; //기록된 것보다 비싸면 패쓰
			Min[ny][nx] = cost;
			q.push({ ny,nx,cost });
		}
	}

}
int main() {
	cin >> N >> M;
	memset(Min, -1, sizeof(Min)); //경로 저장 안된 곳 -1 초기화
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < M; j++) {
			cin >> Cost[i][j];
		}
	}
	Run();
	cout << Min[N-1][M-1];
	return 0;
}