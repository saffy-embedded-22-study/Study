#include <iostream>
#include <cstring>
#include <string>
#include <vector>
using namespace std;


int N, M; //세로 가로
int MAP[10][10];
int Seen[10][10];
int dir[4][2] = { 0,1,1,0,0,-1,-1,0 }; //우 하 좌 상 순서
string d_init[6] = { "0000", "1000", "1010","1001","1011","1111" };
struct cctv {
	int y;
	int x;
	string d;
};
vector<cctv> v;
int n; //cctv 개수
int wall;
int ans; //최소 사각 지대

int Blind() { //cctv방향이 정해진 상태에서 사각지대 크기
	int cnt = 0; //보이는 곳
	memset(Seen, 0, sizeof(Seen));
	for (int i = 0; i < n; i++) {
		cctv now = v[i];
		if (Seen[now.y][now.x] == 0) {
			Seen[now.y][now.x] = 1;
			cnt++;
		}
		if (cnt == N * M - wall) return 0;

		for (int j = 0; j < 4; j++) {
			if (now.d[j] == '0') continue;
			int go = 1;

			while (1) {
				int ny = now.y + go * dir[j][0];
				int nx = now.x + go * dir[j][1];
				if (ny < 0 || nx < 0 || ny >= N || nx >= M) break;
				if (MAP[ny][nx] == 6) break;
				if (Seen[ny][nx] == 0) {
					Seen[ny][nx] = 1;
					cnt++;
				}
				go++;
			}
		}
	}
	return N * M - wall - cnt;
}
void dfs(int lev) {
	if (lev == n) {
		//최소 이면 갱신
		int res = Blind();
		if (ans > res) ans = res;
		return;
	}
	cctv now = v[lev];


	//cctv 돌려보기
	for (int i = 0; i < 4; i++) {
		string temp = now.d + now.d;
		string rotate = temp.substr(i, 4);
		v[lev].d = rotate;

		dfs(lev + 1);

		v[lev].d = temp.substr(0, 4);
	}
}
int main() {
	cin >> N >> M;
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < M; j++) {
			int a; cin >> a;
			MAP[i][j] = a;

			if (a > 0 && a < 6) {//cctv
				v.push_back({ i,j,d_init[a] });
				n++;
			}
			if (a == 6) wall++;
		}
	}
	ans = N * M;
	dfs(0);
	cout << ans;
	return 0;
}