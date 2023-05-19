/*
오름차순으로 정렬 후
지금까지의 합 + 1 보다 다음 수가 크다면 불가능!
*/

#include<bits/stdc++.h>
using namespace std;

int N;
int arr[1000];

int main() {
	ios::sync_with_stdio(false);
	cin.tie(NULL);

	cin >> N;
	for (int i = 0;i < N;++i) {
		cin >> arr[i];
	}
	sort(arr, arr + N);

	int Ans = 1;
	int Max = 0;

	bool flag = false;

	for (int i = 0;i < N;++i) {	
		if (Max + 1 < arr[i]) {
			Ans = Max + 1;
			flag = true;
			break;
		}
		Max += arr[i];
	}
	if (!flag) {	// 다 넣었을때까지 답이 안나올 경우
		Ans = Max + 1;
	}
	cout << Ans;

	return 0;
}
