#include <iostream>
#include <vector>
#define MAX_N 1001
using namespace std;

int N;
bool flag = false;//N 번방 도착 가능여부
vector<int>al[1001];//a[i][0] == 비용
int visited[MAX_N];

void run();
void dfs(int,int);

int main() {
	
	while (true) {
		cin >> N;
		if (N == 0) break;
		for (int i = 1; i <= N; i++) {
			al[i].reserve(N);
		}
		run();
	}

	return 0;
}

void run()
{
	char roomType;
	for (int i = 1; i <= N; i++) {
		int temp;
		cin >> roomType;
		cin >> temp;
		if (roomType == 'T') {//트롤만 맨 처음 수 -로 넣기
			al[i].push_back(-1 * temp);
		}
		else {
			al[i].push_back(temp);
		}
		while (true) {
			int tempInput;
			cin >> tempInput;
			if (tempInput == 0) break;
			al[i].push_back(tempInput);
		}

	}
	
	dfs(1,0);
	//print
	if (flag) cout << "Yes\n";
	else cout << "No\n";
	//reset
	flag = false;
	fill(visited, visited + N + 1, 0);
	for (int i = 1; i <= N; i++) {
		al[i].clear();
	}
}

void dfs(int now, int money) {
	//base
	if (flag == 1) return;
	
	int nowCost = al[now][0];
	int nextMoney = money;
	if (nowCost > 0) {//L
		if (nowCost > money) nextMoney =nowCost;
	}
	if (nowCost < 0) {//T
		if (nowCost * -1 > money) return;
		else nextMoney += nowCost;
	}
	if (now == N) {
		flag = 1;
		return;
	}
	visited[now] = 1;
	//recursive
	int size = al[now].size();
	for (int i = 1; i < size; i++) {
		int next = al[now][i];
		if (visited[next] == 1) continue;
		dfs(next, nextMoney);
	}
	visited[now] = 0;
}
