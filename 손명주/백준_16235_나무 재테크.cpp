#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

struct Node {
	int y;
	int x;
};

// 메모리 2336 kb | 시간 120ms ..^^
int N, M, K; //크기, 나무수, 시간
int Add[10][10]; //추가되는 양분
int Food[10][10]; //양분
int dir[8][2] = { -1,-1,-1,0,-1,1,0,-1,0,1,1,-1,1,0,1,1 };
vector<int> Tree[10][10];
vector<Node> Seed; //번식하는 나무

void Grow(); //자라거나 죽고
void Spread(); //번식
void Feed(); //양분 추가

int main() {
	cin >> N >> M >> K;
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			cin >> Add[i][j];
			Food[i][j] = 5;
		}
	}
	for (int i = 0; i < M; i++) {
		int y, x, age;
		cin >> y >> x >> age;
		Tree[y - 1][x - 1].push_back(age);
	}
	for (int i = 0; i < K; i++) {
		Grow();
		Spread();
		Feed();
	}
	cout << M;
	return 0;
}
void Grow() {
	for (int y = 0; y < N; y++) {
		for (int x = 0; x < N; x++) {
			int n = Tree[y][x].size();
			if (n == 0) continue;

			vector<int> temp;
			int flag = 0;

			for (int i = n - 1; i >= 0; i--) {
				int age = Tree[y][x][i];

				if (flag == 1 || age > Food[y][x]) {
					flag = 1;
					Food[y][x] += age / 2; //나무 사망
					M--;
				}
				else {
					Food[y][x] -= age;
					temp.push_back(age + 1);
					if ((age + 1) % 5 == 0) Seed.push_back({ y,x });
				}
			}
			reverse(temp.begin(), temp.end());
			Tree[y][x].swap(temp);
		}
	}
}
void Spread() {
	int n = Seed.size();
	if (n == 0) return;

	for (int i = 0; i < n; i++) {
		Node now = Seed[i];
		for (int j = 0; j < 8; j++) {
			int ny = now.y + dir[j][0];
			int nx = now.x + dir[j][1];
			if (ny < 0 || nx < 0 || ny >= N || nx >= N) continue;
			Tree[ny][nx].push_back(1);
			M++;
		}
	}
	Seed.clear();
}
void Feed() {
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			Food[i][j] += Add[i][j];
		}
	}
}