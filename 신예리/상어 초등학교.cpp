#include <iostream>
using namespace std;

int N;
int student;
int one_stu;
int like_arr[401][4];
int seat_map[21][21];
int ydir[4] = { -1,1,0,0 };
int xdir[4] = { 0,0,-1,1 };

void find(int); // 한 학생에 대해서 자리 찾아주는 함수
int like_cnt(int, int, int); // 인접한 칸에 좋아하는 학생 수 찾기
int empty_cnt(int, int); // 비어있는 칸 찾기
int result(); // 만족도 계산


int main() {

	ios_base::sync_with_stdio(false);
	cin.tie(NULL); cout.tie(NULL);

	cin >> N;
	student = N * N;

	
	for (int i = 0; i <student; i++) {
		cin >> one_stu;

		for (int j = 0; j < 4; j++) {
			cin >> like_arr[one_stu][j];

		}
		find(one_stu);
	}

	cout << result();

	return 0;
}

void find(int num) {

	int max_like = 0; // 좋아하는 학생의 수가 최대
	int max_empty = 0; // 비어있는 칸이 최대
	int seaty, seatx;

	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			if (seat_map[i][j] != 0) continue; //비어있는 칸이 아니면 패스

			int likecnt = like_cnt(i, j, num); // 좋아하는 학생 칸 계산
			int emptycnt = empty_cnt(i, j); // 비어있는 칸 계산

			if (max_like < likecnt) { // 조건 1
				max_like = likecnt;
				max_empty = emptycnt;
				seaty = i; seatx = j;
			}
			else if (max_like == likecnt && max_empty <= emptycnt) { //조건 2
				max_empty = emptycnt;
				seaty = i; seatx = j;
			}
		}
	}

	seat_map[seaty][seatx] = num;
}

int like_cnt(int y, int x, int num) {

	int cnt = 0;
	for (int i = 0; i < 4; i++) {
		int ny = y + ydir[i];
		int nx = x + xdir[i];

		if (ny < 0 || nx < 0 || ny >= N || nx >= N) continue;

		for (int j = 0; j < 4; j++) {
			if (seat_map[ny][nx] == like_arr[num][j]) { //인접한 칸에 좋아하는 학생있으면 ++
				cnt++;
				break;
			}
		}
	}

	return cnt;
}

int empty_cnt(int y, int x) {

	int cnt = 0;
	for (int i = 0; i < 4; i++) {
		int ny = y + ydir[i];
		int nx = x + xdir[i];

		if (ny < 0 || nx < 0 || ny >= N || nx >= N) continue;
		if (seat_map[ny][nx] == 0) cnt++; // 비어있는 칸이면 ++
	}

	return cnt;
}

int result() {

	int ans = 0;

	for (int y = 0; y < N; y++) {
		for (int x = 0; x < N; x++) {
			int cnt = 0;
			for (int di = 0; di < 4; di++) {
				int ny = y + ydir[di];
				int nx = x + xdir[di];

				if (ny < 0 || nx < 0 || ny >= N || nx >= N) continue;

				for (int k = 0; k < 4; k++) {
					if (seat_map[ny][nx] == like_arr[seat_map[y][x]][k]) {
						cnt++;
						break;
					}
				}
			}

			if (cnt == 1) ans += 1;
			else if (cnt == 2) ans += 10;
			else if (cnt == 3) ans += 100;
			else if (cnt == 4)ans += 1000;
		}
	}

	return ans;
}