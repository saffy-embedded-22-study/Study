#include <iostream>
#include <string>
#include <vector>
#include <queue>
using namespace std;

/*
메모리 : 2240KB
시간 : 0ms
*/

struct yx {
	int y;
	int x;
};

int W, H; // 가로, 세로
string MAP[101]; // 지도
int visited[101][101]; // 방문 체크
int mirror_cnt[101][101]; // 거울 개수 알기 위한 배열
vector<yx>cvect;

int ydir[4] = { -1,1,0,0 };
int xdir[4] = { 0,0,-1,1 };

void bfs(int, int);

int main() {

	ios::sync_with_stdio(false);
	cin.tie(NULL); cout.tie(NULL);

	cin >> W >> H;

	for (int i = 0; i < H; i++) {
		cin >> MAP[i];
	}

	for (int i = 0; i < H; i++) {
		for (int j = 0; j < W; j++) {
			if (MAP[i][j] == 'C') { // C 좌표 벡터에 담아두기
				cvect.push_back({ i,j });
			}
		}
	}
	
	bfs(cvect[0].y, cvect[0].x);// C의 첫번째 좌표에서 시작
	
	int ans = mirror_cnt[cvect[1].y][cvect[1].x] - 1; 

	cout << ans << '\n';

	return 0;

}

void bfs(int y, int x) {

	queue<yx>q;
	q.push({ y,x });
	visited[y][x] = 1;

	while (!q.empty()) {
		yx now = q.front();
		q.pop();
		for (int i = 0; i < 4; i++) {
			int ny = now.y + ydir[i];
			int nx = now.x + xdir[i];
			while (nx >= 0 && ny >= 0 && ny < H && nx < W) { // 같은 방향으로 끝까지 확인하기
				if (MAP[ny][nx] == '*') break; // 벽만나면 나가기
				if (visited[ny][nx] == 0) { // 방문한 적 이 없는 곳이면
					visited[ny][nx] = 1;
					mirror_cnt[ny][nx] = mirror_cnt[now.y][now.x] + 1; // 현재좌표에 +1한 값을 넣어주기
					q.push({ ny,nx }); // 다음 좌표 넣어주기
				}
				ny += ydir[i]; // 같은 방향으로 한칸 더 이동
				nx += xdir[i];
			}
		}
	}
}