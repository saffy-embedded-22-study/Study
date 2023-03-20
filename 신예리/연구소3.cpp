#include<iostream>
#include<vector>
#include<queue>
#include<cstring>
#include<algorithm>
using namespace std;
// 0은 빈 칸, 1은 벽, 2는 바이러스
// M개의 활성화된 바이러스를 dfs를 이용해서 조합으로 뽑기
// result_time 값이 초기값 그대로면 바이러스가 다 퍼지지 않은 상태라서 -1 출력
// 다 퍼진 경우에는 그에 해당하는 result_time값 출력


struct yx {
	int y;
	int x;
};

int ydir[4] = { -1,1,0,0 };//상하좌우
int xdir[4] = { 0,0,-1,1 };

int N, M; // 맵 크기, 활성화된 바이러스 수
int MAP[51][51]; 
int visited[51][51]; //시간계산 배열
int v_cntsize; //바이러스 벡터 사이즈
vector<yx>v_vect; // 바이러스 좌표 담을 벡터
vector<yx>active_v; //활성화된 바이러스 좌표 담을 벡터
int result_time = 9999; //답
queue<yx>q;

void bfs() {

	//dfs로 뽑은 M개의 좌표에서 바이러스 퍼트려주기
	while (!q.empty()) { 
		yx now = q.front();
		q.pop();

		for (int i = 0; i < 4; i++) {
			int ny = now.y + ydir[i];
			int nx = now.x + xdir[i];

			if (ny < 0 || nx < 0 || ny >= N || nx >= N)continue;

			if (MAP[ny][nx] != 1 && visited[ny][nx] == -1) {
				visited[ny][nx] = visited[now.y][now.x] + 1;
				q.push({ ny,nx });
			}
		}
	}
	int max_time = 0;
	int checked = 1;
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			if (MAP[i][j] == 0) {
				if (visited[i][j] == -1) { //모든 빈칸에 바이러스가 퍼지지않은 경우
					checked = 0;
					break;
				}
				else { 
					max_time = max(max_time, visited[i][j]);
				}
			}
		}
	}
	if (checked == 1) { //모든 빈칸에 바이러스가 퍼진 경우에 결과값 갱신
		result_time = min(result_time, max_time);
	}

}


void dfs(int cnt, int ja) {

	//M개의 활성화된 바이러스를 조합으로 뽑아주기
	if (cnt == M) {

		memset(visited, -1, sizeof(visited));

		int active_cnt = active_v.size(); 
		// 활성화된 바이러스들에 대한 좌표 벡터에 담아주기
		for (int i = 0; i < active_cnt; i++) {
			q.push({ active_v[i].y, active_v[i].x });
			visited[active_v[i].y][active_v[i].x] = 0;
		}
		bfs(); 
		return;
	}

	for (int i = ja; i < v_cntsize; i++) {
		active_v.push_back({ v_vect[i].y ,v_vect[i].x });
		dfs(cnt + 1, i + 1);
		active_v.pop_back();
	}

}

int main() {

	ios::sync_with_stdio(false);
	cin.tie(NULL); cout.tie(NULL);


	cin >> N >> M;

	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			cin >> MAP[i][j];
			if (MAP[i][j] == 2) {
				v_vect.push_back({ i,j });
			}
		}
	}

	v_cntsize = v_vect.size();

	dfs(0, 0);
	
	if (result_time == 9999) {
		cout << -1 << '\n';
	}
	else {
		cout << result_time << '\n';
	}

	return 0;
}