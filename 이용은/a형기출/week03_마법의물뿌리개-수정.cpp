#include <iostream>
#include <queue>
#include <algorithm>
using namespace std;

int N;
int Max;//가장 긴 나무 길이
int tree[101];
/*
1. 나무 오름차순 정렬
2. 가장 긴것 부터 check ->
	홀수날 -> Max -2 != 이면 무조건 더하기!
	짝수날 -> Max-2>= 이면 무조건 더하기
*/

void input();
int sol();

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(0);
	int T;
	cin >> T;
	for (int tc = 1; tc <= T; tc++) {
		Max = 0;
		input();
		if (tree[0] == Max) {
			cout << "#" << tc << " 0\n";
			continue;
		}
		cout << "#" << tc << " " << sol() << "\n";
	}


	return 0;
}

void input() {
	cin >> N;
	for (int i = 0; i < N; i++) {
		int tmp;
		cin >> tmp;
		tree[i] = tmp;
	}
	sort(tree, tree + N);
	Max = tree[N - 1];

}

int sol() {
	int day = 0;

	while (true) {
		int flagT = 0;
		int flag = 0;
		day++;
		for (int i = N - 1; i >= 0; i--) {
			if (tree[i] == Max) continue;
			flag = 1;//종료조건 -> 모든 나무 길이 == Max
//홀수날
			if (day % 2 == 1) {
				if (tree[i] != Max - 2) {
					tree[i]++;
					break;//하루 종료
				}
				else {
					if (flagT == 0) {
						//처음 발견
						flagT = 1;
					}
					else {//Max-2 인 나무가 2개 이상이라면 홀수날에도 더한다!
						flagT = 0;
						tree[i]++;
						break;//하루 종료
					}
				}
			}
			else {//짝수날
				if (tree[i] <= Max - 2) {
					tree[i] += 2;
					break;//하루 종료
				}
			}

		}
		if (flag == 0) return day - 1;
	}
}