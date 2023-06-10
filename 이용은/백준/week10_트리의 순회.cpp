#include <iostream>
#include <vector>
#define MAX_N 100000
using namespace std;
int N;
int inOrder[MAX_N];
int postOrder[MAX_N];
vector<int>preOrder;
/*
inOrder : (LC) (root) (RC)
postOrder : (LC) (RC) (root)
preOrder : (root) (LC) (RC)
분할정복
1. postOrder의 맨끝(부모) preOrder에 추가
2. inOrder에서 부모찾기
3. 길이 1 이상인 경우 -> 재귀호출
4. 길이가 1 이면 종료
*/

void divide(int inL, int inR, int postL, int postR) {
	int target = postOrder[postR-1];
	preOrder.push_back({ target });

	if (inL + 1 == inR) return;//길이가 1인 경우

	//inorder에서 target 찾기
	for (int i = inL; i < inR; i++) {
		if (inOrder[i] == target) {
			if (inL != i) {
				divide(inL, i, postL, postL + i - inL);
			}
			if (i + 1 != inR) {
				divide(i + 1, inR, postL + i - inL, postR - 1);
			}
			return;
		}
	}

}

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(0);
	cin >> N;
	for (int i = 0; i < N; i++) cin >> inOrder[i];
	for (int i = 0; i < N; i++) cin >> postOrder[i];

	preOrder.reserve(N);
	divide(0, N,0,N);
	for (int i = 0; i < preOrder.size(); i++) {
		cout << preOrder[i] << " ";
	}

	return 0;
}