#include<iostream>
#include<algorithm>
using namespace std;

struct bag {
	int weight;
	int value;
};

int N; // ����
int K; // ��ƿ �� �ִ� ����
bag arr[101];    // ����, ��ġ ����
int Bag[101][100010];

// ������ �ϳ� ���� �� ���� �ִ밪 ����
// ������ ��Ƶ� ���Կ� ���� ��ġ������ �����ͼ� �̿�
// ������ �� ���� �� ���� �� ���� ���Կ� ���� ��ġ ������ �����ͼ� �� �� �ִ밪 ����

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

	cin >> N >> K; // ��ǰ��, ��ƿ �� �ִ� ����
	for (int i = 1; i <= N; ++i) {
		int W, V;
		cin >> W >> V;
		arr[i].weight = W;
		arr[i].value = V;
	}

	for (int i = 1; i <= N; ++i) {
		for (int j = 1; j <= K; ++j) {
			if (j - arr[i].weight >= 0) {    // ���� ���� �� ���� ��
				Bag[i][j] = max(Bag[i - 1][j], Bag[i - 1][j - arr[i].weight] + arr[i].value);
			}
			else {    // ���� �� ���� ��
				Bag[i][j] = Bag[i - 1][j];
			}
		}
	}

	cout << Bag[N][K] << '\n';

	return 0;
}
