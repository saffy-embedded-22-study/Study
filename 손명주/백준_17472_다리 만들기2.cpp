#include <iostream>
#include <vector>
#include <queue>
using namespace std;

struct Node {
	int y;
	int x;
};
struct Edge {
	int to;
	int dist;
	bool operator < (Edge next) const {
		if (dist > next.dist) return true;
		if (dist < next.dist) return false;
		return false;
	}
};

// 메모리 2028kb | 시간 0ms

int N, M; //세로 가로
int Map[10][10];
int visited[10][10];
int adj[10][10]; //인접 행렬
int L; //섬 개수
int dir[4][2] = { -1,0,1,0,0,-1,0,1 };
vector<Node> coast[10]; //섬 별 테두리
vector<Edge> al[10]; //인접 리스트

void Island(); //섬 탐색
void Fill(int, int);
void Bridge(int); //다리 탐색
int Link(); 

int main() {
	cin >> N >> M;
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < M; j++) {
			int a; cin >> a;
			if (a == 1) a = -1; //체크 안한 섬은 -1
			Map[i][j] = a;
		}
	}
	L = 1;
	Island();
	for (int i = 1; i < L; i++) Bridge(i);
	cout << Link();
	return 0;
}
void Island() {
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < M; j++) {
			if (Map[i][j] == -1) {
				Fill(i, j);
			}
		}
	}
}
void Fill(int sy, int sx) {
	queue<Node> q;
	Map[sy][sx] = L;
	q.push({ sy,sx });
	while (!q.empty()) {
		Node now = q.front();
		q.pop();
		for (int i = 0; i < 4; i++) {
			int ny = now.y + dir[i][0];
			int nx = now.x + dir[i][1];
			if (ny < 0 || nx < 0 || ny >= N || nx >= M) continue;
			if (Map[ny][nx] == 0 && visited[ny][nx] == 0) {
				visited[now.y][now.x] = 1;
				coast[L].push_back({ now.y,now.x }); //테두리 투입
			}
			if (Map[ny][nx] != -1) continue;
			Map[ny][nx] = L;
			q.push({ ny,nx });
		}
	}
	L++;
}
void Bridge(int from) {//섬마다
	int n = coast[from].size();
	for (int i = 0; i < n; i++) {
		Node now = coast[from][i];

		for (int i = 0; i < 4; i++) {
			int ny = now.y + dir[i][0];
			int nx = now.x + dir[i][1];
			if (ny < 0 || nx < 0 || ny >= N || nx >= M) continue;
			if (Map[ny][nx] != 0) continue;

			int go = 1;
			while (1) { //바다로 향하는 방향일 때
				ny += dir[i][0];
				nx += dir[i][1];
				if (ny < 0 || nx < 0 || ny >= N || nx >= M) break;
				if (Map[ny][nx] != 0) {
					if (go == 1) break;
					int to = Map[ny][nx];
					if (adj[from][to] == 0 || adj[from][to] > go) adj[from][to] = go;
					break;
				}
				go++;
			}
		}
	}
}
int Link() {
	for (int i = 1; i < L; i++) {
		for (int j = i + 1; j < L; j++) {
			if (adj[i][j] != 0) {
				al[i].push_back({ j,adj[i][j] });
				al[j].push_back({ i,adj[i][j] });
			}
		}
	}
	priority_queue<Edge> pq;
	int linked[10] = { 0 };
	int cnt = 0;
	int Dist = 0;
	pq.push({ 1,0 });
	while (!pq.empty()) {
		Edge now = pq.top();
		pq.pop();
		if (linked[now.to] == 1) continue;
		linked[now.to] = 1;
		cnt++;
		Dist += now.dist;
		
		int way = al[now.to].size();
		for (int i = 0; i < way; i++) {
			Edge next = al[now.to][i];
			if (linked[next.to] == 1) continue;
			pq.push(next);
		}
	}
	if (cnt == L - 1) return Dist;
	return -1;
}