#include <iostream>
#define MAX_K 10000
using namespace std;
struct Node {
	int A, B, C;
};
int N, K;
int D;
Node rule[MAX_K];

void init();
int ps();
bool condition(int num);

int main() {
	init();
	cout << ps();
	return 0;
}

void init() {
	ios_base::sync_with_stdio(false);
	cin.tie(0);
	cin >> N >> K >> D;
	for (int i = 0; i < K; i++) {
		cin >> rule[i].A >> rule[i].B >> rule[i].C;
	}
}

int ps() {
	int left = 1;
	int right = N;
	int ans = 21e8;

	while (left <= right) {
		int mid = (left + right) / 2;
		if (condition(mid)) {
			ans = mid;
			right = mid - 1;
		}
		else left = mid + 1;
	}
	return ans;
}

bool condition(int num) {
	int cnt = 0;

	for (int i = 0; i < K; i++) {

		if (rule[i].A <= num) {
			if (rule[i].B >= num) {
				cnt += (num - rule[i].A) / rule[i].C + 1;
			}
			else {
				cnt += (rule[i].B - rule[i].A) / rule[i].C + 1;
			}
		}
		if (cnt >= D) return true;
	}
	return false;
}