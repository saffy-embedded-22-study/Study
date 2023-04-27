#include <iostream>
using namespace std;

int N, M; //메모리 2020kb 시간 0ms
int Man[51];
int Party[51]; //첫사람 저장

int Find(int a) {
	if (Man[a] == a || Man[a] == 0) return Man[a];
	return Man[a] = Find(Man[a]);
}
void Union(int a, int b) {
	int pa = Find(a);
	int pb = Find(b);
	if (pa < pb) Man[pb] = pa;
	else Man[pa] = pb;
}
int main() {
	cin >> N >> M;
	for (int i = 1; i <= N; i++) Man[i] = i;
	int truth; cin >> truth;
	for (int i = 0; i < truth; i++) {
		int p; cin >> p;
		Man[p] = 0; //진실인거 0 으로
	}
	for (int i = 1; i <= M; i++) {
		int n; cin >> n; //1이상
		int p0; cin >> p0;
		Party[i] = p0; //Party배열에 첫 번째 참석자 저장
		for (int j = 1; j < n; j++) {
			int p; cin >> p;
			Union(p0, p); //참석자들끼리 한 팀
		}
	}
	int cnt = M;
	for (int i = 1; i <= M; i++) {
		if (Find(Party[i]) == 0) cnt--; //진실아는 사람이면 거짓말 못함
	}
	cout << cnt;
	return 0;
}