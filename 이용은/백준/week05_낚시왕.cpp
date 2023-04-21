#include <iostream>
#include <vector>
#define MAX_N 100
using namespace std;
struct Shark {
	int s, d, z;
};
int R, C, M;//M상어수
vector<int>MAP[MAX_N][MAX_N];//맵에서 제거된 상어 -> 잡은 상어
vector<int>newMAP[MAX_N][MAX_N];

vector<Shark>v;
int ans;// 잡은 상어 크기의 합
int ydir[] = { -1,1,0,0 };//상하우좌
int xdir[] = { 0,0,1,-1 };
/*
catchShark();
	1. ans+= v[i].z
	2. MAP 에서 제거(1개밖에 없음)
	3. M--
eatingShark(); -> 상어가 2마리 이상이면
	맵에 1마리만 남기기
*/

void input();
void run();
void catchShark(int);
void movingShark();
void eatingShark();

int main() {
	input();
	run();
	cout << ans;
	return 0;
}

void input() {
	ios_base::sync_with_stdio(false);
	cin.tie(0);

	cin >> R >> C >> M;
	for (int i = 0; i < M; i++) {
		int r, c, s, d, z;
		cin >> r >> c >> s >> d >> z;
		MAP[r - 1][c - 1].push_back(i);
		d--;
		if (d <= 1) {//상하 인경우
			s %= 2*(R-1);//주기만큼 나눠주기
		}
		else {
			s %= 2*(C - 1);
		}
		v.push_back({ s,d,z });
	}
}


void run() {
	int colIndex = 0;//낙시왕 위치

	while (C != colIndex) {
		if (M == 0) break;//상어를 다 잡은 경우
		catchShark(colIndex++);
		movingShark();
		eatingShark();
	}
}

void catchShark(int idx) {
	for (int i = 0; i < R; i++) {
		if (MAP[i][idx].empty()) continue;
		//상어발견
		Shark now = v[MAP[i][idx][0]];
		ans += now.z;
		MAP[i][idx].pop_back();
		M--;
		break;
	}
}

void movingShark() {


	for (int y = 0; y < R; y++) {
		for (int x = 0; x < C; x++) {
			if (MAP[y][x].empty()) continue;

			Shark now = v[MAP[y][x][0]];//한마리만 존재

			int ndir = now.d;
			int ny = y;
			int nx = x;
			// 이동
			for (int i = 0; i < now.s; i++) {
				ny += ydir[ndir];
				nx += xdir[ndir];
				if (ny >= R || ny < 0 || nx >= C || nx < 0) {//범위 초과시
					ny -= 2*ydir[ndir];
					nx -= 2*xdir[ndir];//복구
					if (ndir % 2 == 0) ndir++;//방향전환
					else ndir--;
					
				}
			}
			v[MAP[y][x][0]].d = ndir;//방향 갱신
			newMAP[ny][nx].push_back(MAP[y][x][0]);//새로운 위치에 저장
		}
	}

	for (int y = 0; y < R; y++) {
		for (int x = 0; x < C; x++) {
			MAP[y][x].clear();
			MAP[y][x]=newMAP[y][x];//기존 맵 대체
			newMAP[y][x].clear();
		}
	}

}
	

void eatingShark() {
	for (int y = 0; y < R; y++) {
		for (int x = 0; x < C; x++) {

			int size = MAP[y][x].size();
			if (size <= 1) continue;

			int bigShark=-1;
			int bigSharkSize = -1;
			//최대크기 상어찾기
			for (int i = 0; i < size; i++) {
				int sharkName = MAP[y][x][i];
				if (v[sharkName].z > bigSharkSize) {
					bigSharkSize = v[sharkName].z;
					bigShark = sharkName;
				}
			}
			MAP[y][x].clear();
			MAP[y][x].push_back(bigShark);
		}
	}
}
