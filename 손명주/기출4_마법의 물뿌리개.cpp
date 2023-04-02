#include <iostream>
using namespace std;

int N;
int Tree[200];
int Max;

int Day() {
	int totDiff = 0;
	int odd = 0;
	for (int i = 0; i < N; i++) {
		int diff = Max - Tree[i];
		totDiff += diff;
		if (diff % 2 == 1) odd++;
	}
	int quo = totDiff / 3;
	int rem = totDiff % 3;
	if (quo >= odd) return quo * 2 + rem;
	else return odd * 2 - 1;
}
int main() {
	int T;
	cin >> T;
	for (int tc = 1; tc <= T; tc++) {
		cin >> N;
		Max = 0;

		for (int i = 0; i < N; i++) {
			int a; cin >> a;
			Tree[i] = a;
			if (a > Max) Max = a;
		}

		cout << "#" << tc << " " << Day() << endl;
	}

	return 0;
}