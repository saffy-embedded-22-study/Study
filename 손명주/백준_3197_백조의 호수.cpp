#include <iostream>
#include <queue>
using namespace std;

int H, W;
char Map[1500][1500];
int visit[1500][1500]; //1 ~ n 다음날 녹을 부분은 -붙여서 넣어둠
int dir[4][2] = { -1,0,1,0,0,-1,0,1 };
int n;
int parent[2500000]; //parent 백조가 1,2번
bool arrive;
struct Node {
	int y, x;
};
Node swan[2];
queue<Node> edge;

void Init(); //호수 부분 플러드필 (백조 있는 위치 부터)
void Melt(); //녹는 부분 4방향 탐색 호수는 union/ 얼음은 녹임
void Fill(int, int);
void Union(int ,int);
int Find(int);

int main() {
	Init();
	int day = 0;
	while (!arrive) {
		Melt();
		day++;
	}
	cout << day;
	return 0;
}
void Init() {
	cin >> H >> W; //input
	for (int i = 0; i < H; i++) {
		for (int j = 0; j < W; j++) {
			cin >> Map[i][j];
			if (Map[i][j] == 'L') {
				swan[n] = { i,j };
				n++;
			}
		}
	}

	n = 0;
	for (int i = 0; i < 2; i++) { //flood fill
		Fill(swan[i].y, swan[i].x);
	}

	for (int i = 0; i < H; i++) {
		for (int j = 0; j < W; j++) {
			if (Map[i][j] == 'X') continue;
			if (visit[i][j]) continue;
			Fill(i, j);
		}
	}

	for (int i = 1; i <= n; i++) parent[i] = i; //parent
}
void Fill(int y, int x) {
	n++;
	queue<Node> q;
	q.push({ y,x });
	if (visit[y][x]) arrive = true;
	visit[y][x] = n;

	while (!q.empty()) {
		Node now = q.front();
		q.pop();

		for (int i = 0; i < 4; i++) {
			int ny = now.y + dir[i][0];
			int nx = now.x + dir[i][1];
			if (ny < 0 || nx < 0 || ny >= H || nx >= W) continue;
			if (visit[ny][nx]!=0) continue;

			if (Map[ny][nx] == 'X') {
				edge.push({ ny,nx });
				visit[ny][nx] = -n;
			}
			else {
				q.push({ ny,nx });
				visit[ny][nx] = n;
			}
		}
	}
}
void Melt() {
	int cursize = edge.size();
	for (int i = 0; i < cursize; i++) {
		Node now = edge.front();
		edge.pop();
		
		int num = -visit[now.y][now.x];
		visit[now.y][now.x] = num;

		for (int j = 0; j < 4; j++) {
			int ny = now.y + dir[j][0];
			int nx = now.x + dir[j][1];
			if (ny < 0 || nx < 0 || ny >= H || nx >= W) continue;

			int next = visit[ny][nx];
			if (next == 0) {
				edge.push({ ny,nx });
				visit[ny][nx] = -num;
			}
			else if (next > 0) {
				Union(next, num);
			}
		}
	}
	if (Find(2) == 1) arrive = true;
}
int Find(int x) {
	if (parent[x] == x) return x;
	return parent[x] = Find(parent[x]);
}
void Union(int a, int b) {
	int pa = Find(a);
	int pb = Find(b);
	if (pa < pb) parent[pb] = pa;
	else parent[pa] = pb;
}