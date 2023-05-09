#include<bits/stdc++.h>
using namespace std;

int N;	// 학생 수
int P;	// 케이블 선 수
int K;	// 공짜 수

struct node {
	int to;
	int cost;

	bool operator < (node next) const {
		return cost > next.cost;
	}
};

vector<node> Map[1001];

void init();
bool Condition(int Num);
int PS();

int main() {
	ios::sync_with_stdio(false);
	cin.tie(NULL);

	init();

	cout << PS();
	return 0;
}

void init() {
	cin >> N >> P >> K;
	for (int i = 0;i < P;++i) {
		int from, to, cost;
		cin >> from >> to >> cost;
		Map[from].push_back({ to,cost });	// 양방향 저장
		Map[to].push_back({ from,cost });
	}
}

bool Condition(int Num) {
	int visited[1001] = { 0 };
	fill_n(&visited[0], 1001, 21e8);	// 초기값 MAX로 설정

	visited[1] = 0;

	priority_queue<node> pq;	// 목적지, Num보다 큰 수
	pq.push({ 1,0 });

	
	while (!pq.empty()) {
		node now = pq.top();
		pq.pop();

		int Size = Map[now.to].size();

		for (int i = 0;i < Size;++i) {
			int Next = Map[now.to][i].to;
			int NCost = Map[now.to][i].cost;
			int NOver = now.cost;
			if (NCost > Num) NOver++;	// 기준값보다 크면 Count + 1
			if (NOver > K) continue;	// Count가 K 보다 커지면 X
			if (visited[Next] <= NOver)continue;	// Count값이 작을때만 이동
			visited[Next] = NOver;
			pq.push({ Next,NOver });
			if (Next == N) return true;
		}

	}

	return false;
}

int PS() {
	int left = 0;
	int right = 1000000;

	int Ans = 21e8;

	while (left <= right) {
		int Mid = (left + right) / 2;

		if (Condition(Mid)) {
			Ans = Mid;
			right = Mid - 1;
		}
		else {
			left = Mid + 1;
		}

	}

	if (Ans == 21e8) return -1;
	else return Ans;
}
