#include <iostream>
#include <queue>
#include <algorithm>
#include <vector>
#include <cstring>
using namespace std;
struct Node {
	int y, x;
};
int N, M;
int ans = 21e8; // 정답
int MAP[50][50];
int visited[50][50] = { 0, };
vector<Node>v;//시작 좌표 저장
vector<Node>path;//dfs 경로 저장
/*
dfs -> 바이러스 놓을 수 있는 위치 중 M개 선택(조합)
now == M 일때 floodfill -> 갈수 있는 곳 모두 가보기
*/

void check() {
	int Max = 0; //visited의 최댓값 -1 ==시간
	for (int y = 0; y < N; y++) {
		for (int x = 0; x < N; x++) {
			//못가본 곳이 있다면 ans 갱신 X
			if (visited[y][x] == 0 && MAP[y][x] == 0) return;
			//시작점은 아닌데 바이러스 활성 후보지라면 -> 시간에 반영 X
			if (MAP[y][x] == 2 && visited[y][x] != 1) continue;
			Max = max(Max, visited[y][x]);
		}
	}
	ans = min(ans, Max-1);
	return;
}

void bfs() {
	memset(visited, 0, sizeof(visited));
	queue<Node>q;
	for (int i = 0; i < M; i++) {
		q.push(path[i]);
		visited[path[i].y][path[i].x] = 1;
	}
	int ydir[] = { -1,1,0,0 };
	int xdir[] = { 0,0,-1,1 };
	
	while (!q.empty()) {
		Node now = q.front();
		q.pop();

		for (int i = 0; i < 4; i++) {
			int ny = now.y + ydir[i];
			int nx = now.x + xdir[i];
			if (ny >= N || nx >= N || ny < 0 || nx < 0) continue;
			if (visited[ny][nx] != 0) continue;
			if (MAP[ny][nx] ==1) continue;
			visited[ny][nx] = visited[now.y][now.x] + 1;
			q.push({ ny,nx });
		}
	}
	check();//후처리
}

void dfs(int now, int st) {
	//base
	if (ans == 0) return;//ans가 0 이면 더 해볼 필요 X
	if (now == M) {
		bfs();
		return;
	}
	//recursive
	int size = v.size();
	for (int i = st; i < size; i++) {
		path.push_back(v[i]);
		dfs(now + 1, i + 1);//조합
		path.pop_back();
	}

}

void input() {
	cin >> N >> M;
	for (int y = 0; y < N; y++) {
		for (int x = 0; x < N; x++) {
			int tmp;
			cin >> tmp;
			MAP[y][x] = tmp;
			if (tmp == 2) {
				v.push_back({ y,x });
			}
		}
	}
}

int main() {
	input();
	dfs(0, 0);

	if (ans == 21e8) {
		cout << -1;
	}
	else cout << ans;
	return 0;
}