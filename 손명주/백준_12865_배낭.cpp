#include <iostream>
#include <algorithm>
using namespace std;

int N, K;
int w[101];
int v[101];
int value[101][100001];
//   1  2  3  4  5  6  7 무게
// 1    (1)------> 1번 들 수 있으면 들음          
// 2    (2)------> 1, 2번 안에서 최대 가치로 들음
// 
// n    (n)------> 
//물품


int main() {
	cin >> N >> K;
	for (int i = 1; i <= N; i++) {
		cin >> w[i] >> v[i];
	}

	for (int i = 1; i <= N; i++) {
		for (int k = 1; k <= K; k++) {
			if (k >= w[i]) value[i][k] = max(value[i - 1][k], value[i - 1][k - w[i]] + v[i]);
			else value[i][k] = value[i - 1][k];
		}
	}
	
	cout << value[N][K];
	return 0;
}
