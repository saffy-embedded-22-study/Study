#include<iostream>
#include<algorithm>
using namespace std;

struct bag {
	int weight;
	int value;
};

int N; // 물건
int K; // 버틸 수 있는 무게
bag arr[101];    // 무게, 가치 정보
int Bag[101][100010];

// 물건을 하나 담을 때 마다 최대값 갱신
// 이전에 담아둔 무게에 대한 가치정보를 가져와서 이용
// 물건을 더 담을 수 있을 때 남은 무게에 대한 가치 정보를 가져와서 비교 후 최대값 갱신

/*
4 7
6 13
4 8
3 6
5 12
*/

int main() {
	ios::sync_with_stdio(false);
	cin.tie(NULL); cout.tie(NULL);

	cin >> N >> K; // 물품수, 버틸 수 있는 무게
	for (int i = 1; i <= N; ++i) {
		int W, V;
		cin >> W >> V;
		arr[i].weight = W;
		arr[i].value = V;
	}

	for (int i = 1; i <= N; ++i) {
		for (int j = 1; j <= K; ++j) {
			if (j - arr[i].weight >= 0) {    // 물건 담을 수 있을 때
				Bag[i][j] = max(Bag[i - 1][j], Bag[i - 1][j - arr[i].weight] + arr[i].value);
			}
			else {    // 물건 못 담을 때
				Bag[i][j] = Bag[i - 1][j];
			}
		}
	}

	cout << Bag[N][K] << '\n';

	return 0;
}
