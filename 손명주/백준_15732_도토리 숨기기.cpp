#include <iostream>
#include <vector>
using namespace std;

struct Rule { //2538kb 4ms
	int start, end, gap;
};
vector<Rule> v;
int N, K, D;//상자 규칙 도토리

bool Dotori(int x) {
	long long cnt = 0;
	for (int i = 0; i < K; i++) {
		int s = v[i].start;
		int e = v[i].end;
		if (s <= x) {
			if (x > e) cnt += (e - s) / v[i].gap + 1; //이거 때문에 계속 틀림 허허
			else cnt += (x - s) / v[i].gap + 1;

			if (cnt >= D) return true;
		}
	}
	return false;
}
int main() {
	ios::sync_with_stdio(0);
	cin.tie(0);

	cin >> N >> K >> D;
	int left = 0;
	int right = N + 1;

	for (int i = 0; i < K; i++) {
		int a, b, c;
		cin >> a >> b >> c;
		v.push_back({ a,b,c });
	}

	while (left + 1 < right) {
		int mid = (left + right) / 2;

		if (Dotori(mid)) right = mid;
		else left = mid;
	}
	cout << right;
	return 0;
}