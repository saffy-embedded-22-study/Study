#include <iostream>
#include <queue>
#include <vector>
#include <algorithm>
#include <utility>
#include <cmath>
using namespace std;
using pii = pair<int, int>;
struct Edge {//prim 용
	int to, dist;
	bool operator <(Edge next) const {
		if (dist < next.dist) return false;
		if (dist > next.dist) return true;
		return false;
	}
};

int N, M;
int MAP[10][10];
queue<pii>nq[8];//섬 좌표 저장
int adj[8][8];
/*
1. 섬찾기 -> 2이상으로 바꾸어 주기
2.  섬에서 다리 만들기 
	->	 경계선X(오히려 헷갈림)
	-> 섬에서 for문으로 4방향 다 돌아보기!
	-> 3중  for문 
			for( 2<= k <= 마지막섬 -1)
					for( 4방향)
						while( )
						섬 찾을때 까지 반복
						최솟값을 인접리스트에 저장!!(양방향 연결) ->다리연결
						거리가 1인 경우는 pass
			
3. 인접행렬 구하면-> MST 찾기 문제로 바꾸기
	pq사용(prim)

*/
int island = 2;//섬 이름



void input(); 
void findIsland();
void bfs(int , int);
void makeBridge();
int prim();


int main() {

	input();
	findIsland();
	makeBridge();
	cout << prim();
	return 0;
}


void input() {
	ios_base::sync_with_stdio(false);
	cin.tie(0);
	cin >> N >> M;
	for (int y = 0; y < N; y++)
		for (int x = 0; x < M; x++) 
			cin >> MAP[y][x];

	for (int y = 0; y < 8; y++) {
		for (int x = 0; x < 8; x++) {
			adj[y][x] = 21e8;//최솟값 구하기 위해 초기값 크게 설정
		}
	}
}

void findIsland() {
	for (int y = 0; y < N; y++) {
		for (int x = 0; x < M; x++) {
			if (MAP[y][x] == 1) {//섬을 2 이상으로 만들어 주기 때문에, 1인경우만 보면 됨
				bfs(y, x);
			}
								
		}
	}
}

void bfs(int sy, int sx) {
	queue<pii>q;
	q.push({ sy,sx });
	nq[island].push({ sy,sx });//다리 잇는 용도
	MAP[sy][sx] = island;//섬이름으로 바꿔주기

	int ydir[] = { -1, 1, 0, 0 };
	int xdir[] = { 0, 0, -1, 1 };
	
	while (!q.empty()) {
		pii Now = q.front();
		q.pop();
		
		for (int i = 0; i < 4; i++) {
			int ny = Now.first + ydir[i];
			int nx = Now.second + xdir[i];
			if (ny >= N || nx >= M || ny < 0 || nx < 0) continue;
			if (MAP[ny][nx] != 1) continue;
			MAP[ny][nx] = island;
			q.push({ ny,nx });
			nq[island].push({ ny,nx });
		}

	}
	island++;
}

void makeBridge() {
	int ydir[] = { -1,1,0,0 };
	int xdir[] = { 0,0, -1, 1 };

	for (int k = 2; k < island-1; k++) {
		while (!nq[k].empty()) {
			pii Now = nq[k].front();
			nq[k].pop();
			
			for (int i = 0; i < 4; i++) {
				int ny = Now.first + ydir[i];
				int nx = Now.second + xdir[i];
				if (ny >= N || nx >= M || nx < 0 || ny < 0) continue;
				if (MAP[ny][nx] == k) continue;//현재 섬이면 -> 다리연결불가
				
				int dist=0;//다른 섬까지 거리
				while (true) {//다른섬 찾기
					ny += ydir[i];
					nx += xdir[i];
					dist++;
					if (ny >= N || nx >= M || nx < 0 || ny < 0) break;
					if (2 <= MAP[ny][nx] && MAP[ny][nx] <= k) break; //(k 이하 섬은 중복)
					if (MAP[ny][nx] >k) {//다른 섬 만난 경우
						if (dist == 1) break;//거리가 1인 다리는 만들지 않음
						adj[k][MAP[ny][nx]] = min(adj[k][MAP[ny][nx]], dist);//다리연결
						adj[MAP[ny][nx]][k] = adj[k][MAP[ny][nx]];//양방향연결
						break;
					}
					
				}
				
			}

		}
	}
}

int prim() {
	//아무 노드부터 시작
	priority_queue<Edge>pq;//MST용
	pq.push({2, 0});

	//MST 일원인지 확인용
	int connected[8] = { 0 };

	int sum = 0;//거리의 합
	int cnt = 0;//연결된 노드수

	while (!pq.empty()) {
		Edge now = pq.top(); //dist가 가장 작은애 빼옴
		pq.pop();
		if (connected[now.to] == 1) continue;
		connected[now.to] = 1;

		sum += now.dist;
		cnt++;

		for (int i = 2; i < island; i++) {
			if (i == now.to) continue;
			if (adj[now.to][i] == 21e8) continue;//다리없는경우 pass
			if (connected[i] == 1) continue;//이미 연결한 경우 pass
			Edge next = { i,adj[now.to][i] };
			pq.push(next);
		}
	}
	if (cnt == island - 2) return sum;
	return -1;
}
