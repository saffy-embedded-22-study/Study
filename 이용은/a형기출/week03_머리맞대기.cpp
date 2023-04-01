#include <iostream>
#include <algorithm>
#include <cstring>
using namespace std;
/*
PS -> 상항선 찾기
condition -> mid값으로 모든 팀을 구성할수 있는지 check
twopointer로 팀구성
*/
int N, T;
int arr[1000];
int arrMax;//입력중 제일 큰값
int ans;

void input();
void PS();
bool condition(int);


int main() {
	input();
	PS();
	cout << ans;
	return 0;
}

void input() {
	arrMax = 0;
	ios_base::sync_with_stdio(false);
	cin.tie(0);
	cin >> N >> T;
	for (int i = 0; i < N; i++) {
		cin >> arr[i];
		arr[i + N] = arr[i];//배열 붙여넣기
		arrMax = max(arr[i], arrMax);//입력중 최댓값 찾기
	}
}

void PS() {
	int st = arrMax;
	int ed = arrMax * (1 + N / T);
	ans = 0;
	while (st <= ed) {
		int mid = (st + ed) / 2;
		if (condition(mid)) {// 가능하면
			ans = mid;
			ed = mid - 1;
		}
		else {
			st = mid + 1;
		}
	}
}

bool condition(int HeadSumMax) {

	for (int i = 0; i < 1 + N / T; i++) {
		int TeamCnt = 1;//나머지 팀
		int Sum = 0;
		for (int j = i; j < N + i; j++) {
			Sum += arr[j];
			if (Sum > HeadSumMax) {//Sum이 더 크다면, 이전꺼(j-1) 까지 한팀임
				TeamCnt++;
				Sum = arr[j];//현재부터 새로운 팀 시작
			}
			if (TeamCnt > T) break;
		}
		if (TeamCnt <= T) return true;//Team수 가 적은거는 OK(나누면 됨)
	}
	return false;
}