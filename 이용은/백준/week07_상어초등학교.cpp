#include <iostream>
#include <cmath>
#include <algorithm>
#include <vector>
#define MAX_N 20
using namespace std;
struct Node {
	int y, x, likeCnt, blankCnt;
};
int Map[MAX_N][MAX_N];
int likePerson[MAX_N*MAX_N+1][4];
int N;

int ydir[] = { 0,0,-1,1 };
int xdir[] = { -1,1,0,0 };


bool cmp(Node left, Node right) {
	if (left.likeCnt > right.likeCnt) return true;
	if (left.likeCnt < right.likeCnt) return false;
	if (left.blankCnt > right.blankCnt) return true;
	if (left.blankCnt < right.blankCnt) return false;
	if (left.y < right.y) return true;
	if (left.y > right.y) return false;
	if (left.x < right.x) return true;
	if (left.x > right.x) return false;
	return false;
}

void input();
void positioning(int);
int sol();

int main() {
	input();
	cout << sol();
	return 0;
}

void input() {
	ios_base::sync_with_stdio(false);
	cin.tie(0);
	cin >> N;
	for (int i = 0; i < N*N; i++) {
		int person;
		cin >> person;
		for (int j = 0; j < 4; j++) {
			cin >> likePerson[person][j];
		}
		positioning(person);
	}
}

void positioning(int now) {
	vector<Node>Position;
	int likeMax = 0;
	int flag = 0;

	for (int y = 0; y < N; y++) {
		for (int x = 0; x < N; x++) {
			if (Map[y][x] != 0) continue;//이미 앉힌 경우
			int likePersonCnt = 0;
			int blankCnt = 0;
			for (int i = 0; i < 4; i++) {
				int ny = y + ydir[i];
				int nx = x + xdir[i];
				if (ny >= N || ny < 0 || nx >= N || nx < 0) continue;
				if (Map[ny][nx] == 0) {//빈칸인경우
					blankCnt++;
					continue;
				}
				//사람이 앉은 경우
				for (int j = 0; j < 4; j++) {
					if (Map[ny][nx] == likePerson[now][j]) {
						likePersonCnt++;
						flag = 1;
						break;
					}
				}
			}

			if (flag == 1 && likeMax > likePersonCnt) continue;
			likeMax = likePersonCnt;
			Position.push_back({ y,x,likePersonCnt, blankCnt });
		}
	}

	sort(Position.begin(),Position.end(), cmp);
	Map[Position[0].y][Position[0].x] = now;
}

int sol() {
	int ans = 0;
	for (int y = 0; y < N; y++) {
		for (int x = 0; x < N; x++) {
			int likeCnt = 0;
			int now = Map[y][x];
			for (int i = 0; i < 4; i++) {
				int ny = y + ydir[i];
				int nx = x + xdir[i];
				if (ny >= N || ny < 0 || nx >= N || nx < 0) continue;
				for (int j = 0; j < 4; j++) {
					if (Map[ny][nx] == likePerson[now][j]) {
						likeCnt++;
						break;
					}
				}
			}
			if (likeCnt != 0) ans += pow(10, likeCnt - 1);
		}
	}
	return ans;
}
