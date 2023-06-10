#include <iostream>
#include <queue>
using namespace std;
struct Node {
	int y, x;
};
int R, C;
int parent[1500 * 1500];
int meltingDay[1500 * 1501];
int Map[1500][1500];
int visited[1500][1500];
Node pos[2]={ -1,-1 ,};
queue<Node>q;
queue<Node>nq;

int ydir[] = { -1,1,0,0 };
int xdir[] = { 0,0,1,-1 };

int Find(int);
void Union(int, int);
void init();
void bfs();

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(0);
	
	init();
	int day = 0;
	while (true) {
		//같은 그룹인지 확인
		if (Find(pos[0].y * 1500 + pos[0].x) == Find(pos[1].y * 1500 + pos[1].x)) {
			cout << day;
			break;
		}
		//아니면 다음 얼음 없애기
		bfs();
		day++;
	}
	
	return 0;
}

int Find(int x) {
	if (parent[x] == x) return x;
	return parent[x] = Find(parent[x]);
}

void Union(int a, int b) {
	int pa = Find(a);
	int pb = Find(b);
	if (pa == pb) return;
	parent[pb] = pa;
}

void init() {
	cin >> R >> C;
	//Union Find 용 초기화
	for (int i = 0; i < R; i++) {
		for (int j = 0; j < C; j++) {
			parent[i * 1500 + j] = i * 1500 + j;
		}
	}
	//입력받기
	for (int i = 0; i < R; i++) {
		for (int j = 0; j < C; j++) {
			char temp;
			cin >> temp;
			Map[i][j] = temp;
			if (temp != 'X') {//'.' 또는 'L' 인경우 -> Union 하기

				if (temp == 'L') {//백조위치 저장
					if (pos[0].y == -1) pos[0] = { i,j };
					else pos[1] = { i,j };
				}

				visited[i][j] = 1;
				q.push({ i,j });

				for (int k = 0; k < 4; k++) {// 인접한 물끼리 Union하기
					int ny = i + ydir[k];
					int nx = j + xdir[k];
					if (ny >= R || ny < 0 || nx >= C || nx < 0) continue;
					if (visited[ny][nx] == 0) continue;
					if (Map[ny][nx] != 'X') Union(1500 * i + j, 1500 * ny + nx);
				}
			}

		}
	}
}

void bfs() {
	int ydir[] = { -1,1,0,0 };
	int xdir[] = { 0,0,1,-1 };

	while (!q.empty()) {
		Node now = q.front();
		q.pop();

		for (int i = 0; i < 4; i++) {
			int ny = now.y + ydir[i];
			int nx = now.x + xdir[i];
			if (ny >= R || ny < 0 || nx >= C || nx < 0) continue;
			if (visited[ny][nx] != 0) continue;
			visited[ny][nx] = visited[now.y][now.x] + 1;
			Map[ny][nx] = '.';
			nq.push({ ny,nx });
		}
	}
	//nq의 원소 -> 없어진 얼음
	//for(4) -> 주위에 물과 Union 해주기
	while (!nq.empty()) {
		Node now = nq.front();
		nq.pop();
		q.push(now);//q 에 옮겨 담기
		for (int i = 0; i < 4; i++) {
			int ny = now.y + ydir[i];
			int nx = now.x + xdir[i];
			if (ny >= R || ny < 0 || nx >= C || nx < 0) continue;
			if (Map[ny][nx] != 'X') Union(now.y * 1500 + now.x, ny * 1500 + nx);
		}
	}
}