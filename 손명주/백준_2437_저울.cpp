#include <iostream>
#include <algorithm>
using namespace std;

int N;
int weight[1000];

int main() {
	cin >> N;
	for (int i = 0; i < N; i++) cin >> weight[i];
	sort(weight, weight + N);//���� �ͺ���
	int now = 1;
	for (int i = 0; i < N; i++) {
		if (now < weight[i]) break;
		now += weight[i];
	}
	cout << now;
	return 0;
}