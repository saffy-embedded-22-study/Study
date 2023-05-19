/*
PS 이용해서 담을 수 있는 도토리 수가 충족되는 수 중 가장 작은 값 찾기!
*/

#include<bits/stdc++.h>
using namespace std;

int N, K, D;
int Rule[10000][3];

void init();
bool Condition(int now);
int PS();

int main() {
	ios::sync_with_stdio(false);
	cin.tie(NULL);

	init();
	cout << PS();


	return 0;
}

void init() {
	cin >> N >> K >> D;
	for (int i = 0;i < K;++i) {
		for (int j = 0;j < 3;++j)
		{
			cin >> Rule[i][j];
		}
	}
}

bool Condition(int now) {
	long long Sum = 0;
	for (int i = 0;i < K;++i) {	// i번째 조건에서 이번 박스까지 몇개를 담을 수 있는지 더하기.
		if (now < Rule[i][0]) continue;
		if (Rule[i][1] <= now) {
			Sum += (Rule[i][1] - Rule[i][0]) / Rule[i][2] + 1;
		}
		else {
			Sum += (now - Rule[i][0]) / Rule[i][2] + 1;
		}
	}
	if (Sum < D) return false;
	else return true;
}

int PS() {
	int left = 0;
	int right = 1000000;

	int Ans = 1;
	while (left <= right) {
		int mid = (left + right) / 2;
		if (Condition(mid) == true) {
			Ans = mid;
			right = mid - 1;
		}
		else {
			left = mid + 1;
		}
	}
	return Ans;
}