#include <iostream>
#include <algorithm>
#define MAX_N 1000
using namespace std;
int N;
int weight[MAX_N];

void init();
int sol();

int main() {
	init();
	cout << sol();
	return 0;
}

void init() {
	ios_base::sync_with_stdio(false);
	cin.tie(0);
	cin >> N;
	for (int i = 0; i < N; i++) {
		cin >> weight[i];
	}
}

int sol() {
	sort(weight, weight + N);
	int Sum = 1;
	for (int i = 0; i < N; i++) {
		if (Sum < weight[i]) break;
		Sum += weight[i];
	}
	return Sum;
}
