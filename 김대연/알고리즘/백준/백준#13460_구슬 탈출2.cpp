#include<bits/stdc++.h>
using namespace std;

int N, M;
char Map[11][11];

bool GameFail = false;	// 파랑공 들어가면
bool GoalIn = false;	// 빨강공 들어가면
int Ans = 11;

void init();
void Gravity();		// 밑으로 내리기
void Turn90();		// 90도 회전시키기
void dfs(int level);

int main() {
	ios::sync_with_stdio(false);
	cin.tie(NULL);

	init();
	
	dfs(1);

	if (Ans == 11) cout << -1;
	else cout << Ans;

	return 0;
}

void init() {
	cin >> N >> M;
	for (int i = 0; i < N; ++i) {
		string temp;
		cin >> temp;
		for (int j = 0; j < M; ++j) {
			Map[i][j] = temp[j];
		}
	}
}


void Gravity() {	// 아래방향으로 내리기

	for (int j = 1; j < 9; ++j) {
		if (Map[0][j] == 0) break;

		bool flag = false;
		int floor = 9;
		int Hole = 10;

		for (int i = 1; i < 10; ++i) {	// R, B 있는지 확인
			if (Map[i][j] == 0) {
				floor = i - 2;
				break;
			}
			if (Map[i][j] == 'R' || Map[i][j] == 'B') {
				flag = true;
			}
		}
		if (!flag) continue;



		for (int i = floor; i > 0; --i) {
			if (Map[i][j] == '#') {
				floor = i - 1;
			}
			else if (Map[i][j] == 'O') {
				Hole = i;
			}
			else if (Map[i][j] == 'R' || Map[i][j] == 'B') {
				if (floor >= Hole) {
					if (Map[i][j] == 'R') {
						GoalIn = true;
						Map[i][j] = '.';
					}
					else {
						GameFail = true;
						return;
					}
				}
				else {
					char temp = Map[i][j];
					Map[i][j] = '.';
					Map[floor--][j] = temp;
				}
			}
		}
		if (GoalIn || GameFail) return;
	}
}

void Turn90() {
	char TempMap[11][11] = { 0 };

	int NowN = 0;

	for (int i = 0; i < 10; ++i) {	// 세로 길이 측정
		if (Map[i][0] == 0) break;
		NowN++;
	}

	for (int i = 0; i < 10; ++i) {
		for (int j = 0; j < 10; ++j) {
			if (Map[i][j] == 0) break;
			TempMap[j][NowN - i - 1] = Map[i][j];
		}
	}
	memcpy(Map, TempMap, sizeof(TempMap));
}

void dfs(int level) {
	if (level == 11) {
		return;
	}
	if (Ans <= level) {
		return;
	}

	char SaveMap[11][11] = { 0 };


	for (int i = 0; i < 4; ++i) {
		memcpy(SaveMap, Map, sizeof(Map));

		Gravity();	// 내리기

		if (!GameFail && GoalIn) {	// 빨간공만 들어갔을때
			Ans = min(Ans, level);
			GoalIn = false;
		}
		else if (GameFail) {		// 파란공 들어갔을때
			GameFail = false;
			GoalIn = false;		
		}
		else {
			dfs(level + 1);
		}
		
		memcpy(Map, SaveMap, sizeof(SaveMap));	// 내린거 복구
		Turn90();
	}

}