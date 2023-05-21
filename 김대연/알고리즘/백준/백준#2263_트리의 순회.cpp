/*
포스트오더의 마지막은 항상 노드.
인오더에서는 노드를 중심으로 좌 우로 나눠짐.

인오더		8 4 9 2 5 1 6 3 7
포스트오더	8 9 4 5 2 6 7 3 1

첫 루트 1

인오더		8 4 9 2 5 / 1 / 6 3 7
포스트오더	8 9 4 5 2 / 6 7 3 / 1

다음 루트 2 , 3

인오더		8 4 9 / 2 / 5		6 / 3 / 7
포스트오더	8 9 4 / 5 / 2		6 / 7 / 3

이런식으로 구하면 프리오더는 1 2 4 8 9 5 3 6 7
*/

#include<bits/stdc++.h>
using namespace std;

int n;

int Inorder[100001];
int Postorder[100001];
int Pos[100001];

void init();
void Solve(int InStart, int InEnd, int PostStart, int PostEnd);

int main() {
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	
	init();

	Solve(0, n - 1, 0, n - 1);

	return 0;
}

void init() {
	cin >> n;
	for (int i = 0; i < n; ++i) {
		cin >> Inorder[i];
		Pos[Inorder[i]] = i;	// Inorder에서 몇번째에 위치해있는지 저장
	}
	for (int i = 0; i < n; ++i) {
		cin >> Postorder[i];
	}
}

void Solve(int InStart, int InEnd, int PostStart, int PostEnd) {	// 인오더 시작, 끝, 포스트오더 시작, 끝

	int Root = Postorder[PostEnd];	// 포스트오더 마지막 = 루트
	int RootPos = Pos[Root];	// 인오더에서 루트가 몇번째에 위치해있는지 확인
	cout << Root << ' ';	// 루트 출력 ( 프리오더는 루트 > left > right 순서)

	int leftcnt = RootPos - InStart;	// 루트 기준으로 왼쪽 오른쪽에 몇개 있는지 확인.
	int rightcnt = InEnd - RootPos;		// 이건 필요 없음.

	if (InStart == InEnd) return;	// 둘이 같으면 자식이 없음.

	if(InStart <= RootPos -1)	
		Solve(InStart, RootPos - 1, PostStart, PostStart + leftcnt - 1);	// 인오더 시작~루트 전, 포스트 시작 ~ 갯수만큼
	if (RootPos+1 <= InEnd)
		Solve(RootPos + 1, InEnd, PostStart + leftcnt, PostEnd - 1);	// 인오더 루트 다음~ 끝, 포스트 마지막 빼고 나머지
}