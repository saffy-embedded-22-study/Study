#include <iostream>
#include <queue>
using namespace std;
// 0,0���� N-1,M-1���� ���� �Ǽ�
// visited[N-1][M-1]�� ����
// �Ǽ� �Ұ����� ���� -1

int N; // ����
int M; // ���� 
int MAP[1001][1001]; // ��
int visited[1001][1001]; // ��� ��
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
			if (ny < 0 || nx < 0 || ny >= N || nx >= M) continue; //���� �������� 
			if (MAP[ny][nx] == -1) continue; // ħ���� ���� ��������
			
			int ncost = now.cost + MAP[ny][nx]; //���ο� ���

			if (ncost >= visited[ny][nx]) continue; // ���ο� ����� �� ũ�� �ѱ��

			visited[ny][nx] = ncost;
			pq.push({ ny, nx, ncost }); //���ο� ��ǥ, ������� ����
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

