/*
지난번 풀이 : Union-Find 이용해서 팀 나누기

이번 풀이 : dfs 만으로 해결!

1. dfs 이용해서 조합 구성. 평범한 방식으로는 놓치는 경우가 생김!
	ex) Y자 같은 경우 1- 2- 3		
			    ㅣ
			    4	
2. solve 함수를 이용해서 두 구간의 합 차이 구하기!
	- 우선 나머지 지역들이 이어져있는지 확인!
	- 다 이어져있으면 각 팀간의 점수 합 구해서 차이 구하기!

3. solve 함수 계산할때마다 visited 구성을 2진법으로 저장하여 중복방지!


*/

#include<bits/stdc++.h>
using namespace std;

int N;	// 지역 수
int arr[11];	// 사람 수
vector<int> Link[11];	// 연결 정보
int visited[11];	// 연결 체크
int ans = 9999;		// 정답
int DAT[1500];	// 중복체크

void init() {
	memset(arr, 0, sizeof(arr));
	memset(visited, 0, sizeof(visited));
	ans = 9999;
	memset(DAT, 0, sizeof(DAT));
	for (int i = 0; i < 11; ++i) {
		Link[i].clear();
	}

	cin >> N;
	for (int i = 1; i <= N; ++i) {
		for (int j = 1; j <= N; ++j) {
			int temp;
			cin >> temp;
			if (temp == 1) {
				Link[i].push_back(j);
			}
		}
	}

	
	for (int i = 1; i <= N; ++i) {
		cin >> arr[i];
	}
}

int solve() {
	int check[11];
	memcpy(check, visited, sizeof(visited));

	queue<int> q;

	for (int i = 1; i <= N; ++i) {
		if (check[i] == 0) {	// 연결 안된 지점 하나 찾기
			q.push(i);
			check[i] = 2;
			break;
		}
	}


	while (!q.empty()) {
		int now = q.front();
		q.pop();

		int len = Link[now].size();
		for (int i = 0; i < len; ++i) {
			int next = Link[now][i];
			if (check[next] != 0)continue;
			check[next] = 2;
			q.push(next);
		}
	}
	
	

	int sum1 = 0;
	int sum2 = 0;

	for (int i = 1; i <= N; ++i) {
		if (check[i] == 1) sum1 += arr[i];
		else if (check[i] == 2) sum2 += arr[i];
		else return -1;	// 연결 안된 지역이 있으면 조건 충족 X
	}

	return abs(sum1 - sum2);
}

void dfs(int cnt) {	// cnt는 연결된 지역 수
	if (cnt == N) return;	// N개가 다 연결되기전까지만!

	// 계산
	int checknum = 0;

	// 중복방지 중요!!!
	for (int i = 1; i <= N; ++i) {	// 2진수로 저장
		checknum *= 2;	
		if (visited[i] == 1) {
			checknum += 1;
		}
	}
	if (DAT[checknum] == 1)return;

	int nowans = solve();
	if (nowans != -1) 	// 더 해볼 필요 X
	{
		ans = min(ans, nowans);
	}
	DAT[checknum] = 1;

	// dfs
	for (int i = 1; i <= N; ++i) {
		if (visited[i] == 0)continue;	// 연결된 지점만

		int len = Link[i].size();
		for (int j = 0; j < len; ++j) {
			int next = Link[i][j];	// 다음 목적지
			if (visited[next] == 1)continue;
			visited[next] = 1;
			dfs(cnt + 1);
			visited[next] = 0;
		}
	}



}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(NULL); 

	int T;
	cin >> T;
	
	for (int tc = 1; tc <= T; ++tc) {
		init();
		visited[1] = 1;
		dfs(1);

		cout << "#" << tc << ' ';
		if (ans == 9999)cout << -1<<'\n';
		else
		{
			cout << ans << '\n';
		}
	}
	

	return 0;
}
