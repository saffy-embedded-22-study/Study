#include <iostream>
#include <queue>
using namespace std;
// 0,0에서 N-1,M-1까지 도로 건설
// visited[N-1][M-1]이 정답
// 건설 불가능일 때는 -1

int N; // 세로
int M; // 가로 
int MAP[1001][1001]; // 맵
int visited[1001][1001]; // 비용 맵
int ans;

int ydir[4] = { -1, 1, 0, 0 };
int xdir[4] = { 0, 0, -1, 1 };

struct yx {
	int y;
	int x;
	int cost;

	bool operator <(yx next) const {
		if (cost > next.cost)return true;
		if (cost < next.cost)return false;
		return false;
	}
};


void bfs(int sy, int sx, int scost)
{
	priority_queue<yx> pq;

	pq.push({ sy, sx, scost });
	visited[0][0] = scost;

	while (!pq.empty()){
		yx now = pq.top();
		pq.pop();

		if (visited[now.y][now.x] < now.cost) continue;

		for (int i = 0; i < 4; i++){
			int ny = now.y + ydir[i];
			int nx = now.x + xdir[i];
			if (ny < 0 || nx < 0 || ny >= N || nx >= M) continue; //경계면 지나가기 
			if (MAP[ny][nx] == -1) continue; // 침수된 도로 지나가기
			
			int ncost = now.cost + MAP[ny][nx]; //새로운 비용

			if (ncost >= visited[ny][nx]) continue; // 새로운 비용이 더 크면 넘기기

			visited[ny][nx] = ncost;
			pq.push({ ny, nx, ncost }); //새로운 좌표, 비용으로 갱신
		}
	}
}


int main()
{
	ios::sync_with_stdio(false);
	cin.tie(NULL); cout.tie(NULL);

	cin >> N >> M;
	for (int i = 0; i < N; ++i){
		for (int j = 0; j < M; ++j){
			cin >> MAP[i][j];
			visited[i][j] = 21e8;
		}
	}

	bfs(0,0,MAP[0][0]);

	ans = visited[N - 1][M - 1];

	if (ans == 21e8) {
		cout << -1;
	}
	else cout << ans;

	return 0;
}

