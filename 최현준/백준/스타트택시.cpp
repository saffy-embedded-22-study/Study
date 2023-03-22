/*
손님을 태우는 함수 driveToCustomer와
손님을 태우고 목적지까지 가는 함수 driveToDest 함수를 선언하여
두 함수를 번갈아가면서 사용하여 결과값을 뽑았습니다.
*/

#include <iostream>
#include <cstring>
#include <algorithm>
#include <string>
#include <vector>
#include <queue>
using namespace std;

// 함수 선언
void driveToCustomer(int y, int x, int nfuel, int cnt);
void driveToDest(int y, int x, int dest, int nfuel, int cnt);

int n, m, fuel;

int road[22][22];
int visited[22][22] = { 0, };

struct node {
	int y;
	int x;
	int time;
	bool operator<(node next) const {
		if (time > next.time) return true;
		if (time < next.time) return false;
		if (y > next.y) return true;
		if (y < next.y) return false;
		if (x > next.x)return true;
		if (x < next.x)return false;
		return false;
	}
};

struct pos {
	int y;
	int x;
};

//Dest : 각 인원의 목적지 좌표를 저장하는 벡터
vector<pos> Dest;
priority_queue<node>pq;

int ydir[4] = { -1,0,1,0 };
int xdir[4] = { 0,-1,0,1 };

// 출발좌표, 연료량, 남은 손님수를 변수로 받음.
void driveToCustomer(int y, int x, int nfuel, int cnt)
{
	//남은 손님수가 0일 때의 연료량을 출력
	if (cnt == 0)
	{
		cout << nfuel;
		return;
	}

	//pq 초기화 및 초기 세팅
	while (!pq.empty())
		pq.pop();
	pq.push({ y,x,0 });
	memset(visited, 0, sizeof(visited));
	visited[y][x] = 1;

	//bfs 시작
	while (!pq.empty())
	{
		node now = pq.top(); pq.pop();

		int y = now.y;
		int x = now.x;
		int time = now.time;

		// time(움직인 거리)가 연료량 보다 클 때 불가능한 경우이기 때문에 -1 출력
		if (time > nfuel)
		{
			cout << "-1";
			return;
		}

		//조건이 road[y][x] >0 인 이유 : 4방향 탐색하며 pq에 추가하는 과정에서 road 값이 1(벽)인 경우는 넣어주지 않기 때문에
		if (road[y][x] > 0)
		{
			//main에서  road에 2부터 값을 넣어줬기 때문에 vector Dest의 index의 표현을 위해 2를 빼줌
			int dest = road[y][x] - 2;
			road[y][x] = 0;
			driveToDest(y, x, dest, nfuel-time, cnt);
			return;
		}

		for (int i = 0; i < 4; ++i)
		{
			int ny = now.y + ydir[i];
			int nx = now.x + xdir[i];
			int ntime = now.time + 1;

			if (visited[ny][nx]) continue;
			if (ny <= 0 || nx <= 0 || ny > n || nx > n) continue;
			if (road[ny][nx] == 1) continue;

			visited[ny][nx] = 1;
			pq.push({ ny,nx,ntime });
		}
	}

	cout << "-1";

}

void driveToDest(int y, int x, int dest, int nfuel, int cnt)
{
	while (!pq.empty())
		pq.pop();
	pq.push({ y,x,0 });
	memset(visited, 0, sizeof(visited));
	visited[y][x] = 1;

	//dest(index)값을 받아 Dest에서 태운 인원의 목적지 좌표 값을 불러온다.
	int dest_y = Dest[dest].y;
	int dest_x = Dest[dest].x;

	while (!pq.empty())
	{
		node now = pq.top(); pq.pop();

		int y = now.y;
		int x = now.x;
		int time = now.time;


		// time(움직인 거리)가 연료량 보다 클 때 불가능한 경우이기 때문에 -1 출력
		if (time > nfuel)
		{
			cout << "-1";
			return;
		}

		// 목적지에 도착했을 때 손님 수를 빼주고 driveToCustomer 함수 호출
		if (y == dest_y && x == dest_x)
		{
			driveToCustomer(y, x, nfuel+time, cnt - 1);
			return;
		}

		for (int i = 0; i < 4; ++i)
		{
			int ny = now.y + ydir[i];
			int nx = now.x + xdir[i];
			int ntime = now.time + 1;

			if (visited[ny][nx]) continue;
			if (ny <= 0 || nx <= 0 || ny > n || nx > n) continue;
			if (road[ny][nx] == 1) continue;

			visited[ny][nx] = 1;
			pq.push({ ny,nx,ntime });
		}
	}

	cout << "-1";
}

int main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(NULL); cout.tie(NULL);

	cin >> n >> m >> fuel;

	for (int i = 1; i <= n; ++i)
	{
		for (int j = 1; j <= n; ++j)
		{
			cin >> road[i][j];
		}
	}

	int driver_y, driver_x;
	cin >> driver_y >> driver_x;

	// 출발지점은 겹치지 않기 때문에 도로 정보가 들어있는 road 배열에 직접 넣으려고 함. (1은 벽이기 때문에 2부터 m+1까지 값을 넣어줌)
	// 도착지점은 Dest 벡터에 넣어줬음.
	for (int i = 2; i <= m+1; ++i)
	{
		int y, x;
		cin >> y >> x;
		road[y][x] = i;
		cin >> y >> x;
		Dest.push_back({ y,x });
	}

	driveToCustomer(driver_y, driver_x, fuel, m);
	return 0;
}