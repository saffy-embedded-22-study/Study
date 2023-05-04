#include <iostream>
using namespace std;

struct Node {
	int y, x, like, blank;
};
int N;  //2032kb 4ms
int Seat[21][21];
int Like[500][4];
int dir[4][2] = { -1,0,1,0,0,-1,0,1 };

void Find(int n); //n학생 앉히기
int Result(); //만족도

int main() {
	cin >> N;
	for (int i = 0; i < N * N; i++) {
		int p; cin >> p;
		for (int j = 0; j < 4; j++) {
			cin >> Like[p][j];
		}
		Find(p);
	}
	cout << Result();
	return 0;
}
void Find(int n) {
	Node res = { 0,0,0,0 }; //학생n 자리 : 0,0 에서 시작
	for (int y = 0; y < N; y++) {
		for (int x = 0; x < N; x++) { //조건3
			if (Seat[y][x] != 0) continue;

			int like = 0; int blank = 0;
			for (int i = 0; i < 4; i++) {
				int ny = y + dir[i][0];
				int nx = x + dir[i][1];
				if (ny < 0 || nx < 0 || ny >= N || nx >= N) continue;
				int here = Seat[ny][nx];
				if (here == 0) blank++;
				else if (here == Like[n][0] || here == Like[n][1] || here == Like[n][2] || here == Like[n][3]) like++;
			}

			if (res.like < like) res = { y,x,like,blank }; //조건1 -> 좋아하는 학생이 많은 자리로
			else if (res.like == like && res.blank < blank) res = { y,x,like,blank }; //조건2 -> 빈칸이 많은 자리로
			else if (Seat[res.y][res.x] != 0) res = { y,x,like,blank }; // 0,0이 남의 자리인 경우 다른 자리로
		}
	}
	Seat[res.y][res.x] = n;
}
int Result() {
	int Sum = 0;
	for (int y = 0; y < N; y++) {
		for (int x = 0; x < N; x++) {
			int like = 0;
			int n = Seat[y][x];
			for (int i = 0; i < 4; i++) {
				int ny = y + dir[i][0];
				int nx = x + dir[i][1];
				if (ny < 0 || nx < 0 || ny >= N || nx >= N) continue;
				int here = Seat[ny][nx];
				if(here == Like[n][0] || here == Like[n][1] || here == Like[n][2] || here == Like[n][3]) like++;
			}
			int dec = 1;
			for (int i = 1; i < like; i++)dec *= 10;
			if (like == 0) dec = 0;
			Sum += dec;
		}
	}
	return Sum;
}