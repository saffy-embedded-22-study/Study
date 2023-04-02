/*
DP 구성

물건이 추가될때마다 배낭 무게가 1~K 일때의 최대가치를 갱신하는 방식.

		1	2	3	4	5	6	7	배낭 무게		
6(13)	0	0	0	0	0	13	13	
4(8)	0	0	0	8	8	13	13
3(6)	0	0	6	8	8	13	14
5(12)	0	0	6	8	12	13	14
무게(가치)

물건 하나를 담을때마다 배낭에 담을 수 있는 최대 가치 확인.
기본적으로 지난 물건까지 담았을때의 가치를 가져오는 방식. DP[i][k] = DP[i-1][k]
이번 물건을 담았을때 남은 무게만큼 물건을 더 담을 수 있음!
	-> 이를 바로 윗줄에서 확인! 
	ex) (3,7)에서 3을 담으면 4가 남음. 그럼 4무게 만큼 물건을 더 담을 수 있음!
	이를 (2,4)에서 가져오면 8 + 6 > 13 이므로 더 큰 값을 찾을 수 있음!
	이런식으로 갱신하면 DP[N][K] 값이 최대값!


*/


#include<bits/stdc++.h>
using namespace std;

int N;	// 물품 수
int K;	// 버틸 수 있는 무게
int arr[101][2];	// 무게, 가치 정보
int DP[101][100010];

void init() {
	cin >> N >> K;
	for (int i = 1; i <= N; ++i) {
		cin >> arr[i][0] >> arr[i][1];
	}
}

int solve() {

	for (int i = 1; i <= N; ++i) {
		for (int k = 1; k <= K; ++k) {
			if (k < arr[i][0]) {	// 이번 물건을 못 넣을 때.
				DP[i][k] = DP[i - 1][k];
			}
			else {	// 이번 물건을 담을 수 있을 때!
				DP[i][k] = max(DP[i - 1][k - arr[i][0]] + arr[i][1], DP[i - 1][k]);
			}
		}
	}

	return DP[N][K];
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(NULL);

	init();
	cout << solve() << '\n';

	return 0;
}