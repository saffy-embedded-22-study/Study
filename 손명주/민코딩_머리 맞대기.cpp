#include <iostream>
#include <cstring>
using namespace std;

int N, T;
int Head[500]; //두뇌 회전 속도
int Cut[500]; // 0 ^ 1 2 ^ 3 이렇게 잘리면 12 03 팀
int Sum[500]; //팀별 합
int Min; // 정답 (최소 Max Sum)

int Calc() {
	memset(Sum, 0, sizeof(Sum));
	int team = 0;
	int max = 0;
	for (int i = 0; i < N; i++) {
		if (Cut[i] == 1) {
			if (Sum[team] > max) max = Sum[team];
			team++;
		}
		Sum[team] += Head[i];
	}
	Sum[0] += Sum[team];
	if (Sum[0] > max) max = Sum[0];

	return max;
}
void Run(int lev, int to) {
	if (lev == T) {
		if (Min > Calc()) Min = Calc();
		return;
	}
	for (int i = to; i <= N - (T - lev); i++) {
		Cut[i] = 1;
		Run(lev + 1, i + 1);
		Cut[i] = 0;
	}
}
int main() {
	cin >> N >> T;
	for (int i = 0; i < N; i++) cin >> Head[i];

	Min = 999999999;
	Run(0, 0);
	cout << Min;

	return 0;
}