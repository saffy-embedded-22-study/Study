#include <iostream>
#include <vector>
#include <algorithm>
#define MAX_N 11
using namespace std;

struct Tree {
	int age, isAlive;
};
int N, M, K;
int Land[MAX_N][MAX_N];
int A[MAX_N][MAX_N];//추가되는 양분의 양
vector<Tree>tree[MAX_N][MAX_N];

bool cmp(Tree left, Tree right) {
	if (left.age > right.age) return true;
	if (left.age < right.age) return false;
	return false;
}

void input();
void run();
void spring();
void summer();
void fall();
void winter();
void print();

int main() {
	input();
	run();
	print();
	return 0;
}

void input() {
	ios_base::sync_with_stdio(false);
	cin.tie(0);
	cin >> N >> M >> K;
	for (int y = 1; y <= N; ++y) {
		for (int x = 1; x <= N; ++x) {
			cin >> A[y][x];
			Land[y][x] = 5;//초기 양분 5
		}
	}
	for (int i = 0; i < M; ++i) {
		int x, y, z;//순서주의
		cin >> x >> y >> z;
		tree[x][y].push_back({ z, 1 });
	}
}

void run() {
	while (K--) {
		spring();
		summer();
		fall();
		winter();
	}
}
//양분먹고 나이증가
void spring() {
	for (int y = 1; y <= N; ++y) {
		for (int x = 1; x <= N; ++x) {
			if (tree[y][x].empty()) continue;
			int treeCnt = tree[y][x].size();

			for (int i = treeCnt-1; i >=0; --i) {//제일 어린나무가 뒤에있음
				Tree now = tree[y][x][i];
				if (now.age > Land[y][x]) {
					tree[y][x][i].isAlive = 0;
					continue;
				}

				Land[y][x] -= now.age;
				tree[y][x][i] = { now.age + 1,1 };
			}

		}
	}
}
//죽은나무 양분으로 변환
void summer() {
	for (int y = 1; y <= N; ++y) {
		for (int x = 1; x <= N; ++x) {
			if (tree[y][x].empty()) continue;

			vector<Tree>temp;//살아있는 나무 저장용

			int treeCnt = tree[y][x].size();
			for (int i = 0; i < treeCnt; ++i) {
				Tree now = tree[y][x][i];
				if (now.isAlive == 0) {
					Land[y][x] += now.age / 2;
				}
				else {//살아있는 나무만 저장
					temp.push_back(now);
				}
			}
			tree[y][x] = temp;//살아있는 나무만 가져오기
		}
	}
}
//번식
void fall() {
	int ydir[] = { -1,-1,-1,0,0,1,1,1 };
	int xdir[] = { -1,0,1,-1,1,-1,0,1 };

	for (int y = 1; y <= N; ++y) {
		for (int x = 1; x <= N; ++x) {
			if (tree[y][x].empty()) continue;

			int treeCnt = tree[y][x].size();
			for (int i = 0; i < treeCnt; ++i) {
				Tree now = tree[y][x][i];
				if (now.age % 5 == 0) {
					for (int j = 0; j < 8; ++j) {
						int ny = y + ydir[j];
						int nx = x + xdir[j];
						if (ny > N || ny <= 0 || nx > N || nx <= 0) continue;
						tree[ny][nx].push_back({ 1,1 });//제일어린나무> 뒤에 추가
					}
				}
			}
		}
	}
}
//양분추가
void winter() {
	for (int y = 1; y <= N; ++y) {
		for (int x = 1; x <= N; ++x) {
			Land[y][x] += A[y][x];
		}
	}
}
//정답출력
void print() {
	int treeCnt = 0;
	for (int y = 1; y <= N; ++y) {
		for (int x = 1; x <= N; ++x) {
			treeCnt += tree[y][x].size();
		}
	}
	cout << treeCnt;
}