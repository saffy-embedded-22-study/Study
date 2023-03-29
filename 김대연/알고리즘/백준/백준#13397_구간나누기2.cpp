/*
1. PS를 이용하여 최소값 찾기. 그룹을 지을 수 있는 최대값을 기준으로 잡음!
2. condition에서 최대값을 기준으로 몇개의 그룹을 만들 수 있는지 체크.
	M개 이상 만들어지면 false!
*/

#include<bits/stdc++.h>
using namespace std;

int N;	// 배열의 크기
int M;	// 구간 개수
int arr[5050];	// 수 저장

void init() {
	cin >> N >> M;
	for (int i = 0; i < N; ++i) {
		cin >> arr[i];
	}
}

bool condition(int cut) {	// cut : 그룹 만들 수 있는 최대값
	int Min = arr[0];
	int Max = arr[0];
	int cnt = 1;

	for (int i = 0; i < N; ++i) {
		Min = min(Min, arr[i]);
		Max = max(Max, arr[i]);

		int diff = Max - Min;

		if (diff > cut) {	// 그룹의 최대값 - 최소값이 cut 보다 커지면 X
			cnt++;
			Min = arr[i];	// i번째 부터 그룹 다시 시작
			Max = arr[i];
		}
	}
	if (cnt <= M) {	// 만들어진 그룹이 M개 이하면 true
		return true;
	}
	else {
		return false;
	}
}

int PSearch() {
	int left = 0;
	int right = 10000;

	int mid; 
	int ans;	

	while (left <= right) {
		mid = (left + right) / 2;
		if (condition(mid) == true) {
			ans = mid;
			right = mid - 1;
		}
		else {
			left = mid + 1;
		}
	}
	return ans;
}


int main() {
	ios::sync_with_stdio(false);
	cin.tie(NULL);

	init();

	cout << PSearch();

	return 0;
}