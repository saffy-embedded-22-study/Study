#include <iostream>
#include <vector>
#define MAX_N 50
#define MAX_M 50
using namespace std;

int N, M;
int trueManCnt;//진실 아는 사람 수
int heardTrue[MAX_N + 1]; // index : 사람 |  value : 진실 들어봣는지?
vector<int>party[MAX_M];//index : 파티 이름 | value : 참여하는 사람
vector<int>falseParty;// value : false party 인 '가능성' 있는 파티


void input();
void trueParty(int);//파티 구성원 heardTrue = 1로 만들기
int findFalseParty();

int main() {
	input();
	if (trueManCnt == 0) {
		cout << M;
		return 0;
	}
	cout << findFalseParty();
	return 0;
}

void input() {
	cin >> N >> M >> trueManCnt;
	for (int i = 0; i < trueManCnt; i++) {
		int trueMan;
		cin >> trueMan;
		heardTrue[trueMan] = 1;
	}
	
	for (int i = 0; i < M; i++) {
		bool flag = false;//거짓 파티인지 확인용
		int cnt;
		cin >> cnt;
		for (int j = 0; j < cnt; j++) {
			int partyMember;
			cin >> partyMember;
			if (heardTrue[partyMember] == 1) flag = true;//진실파티
			party[i].push_back(partyMember);
		}
		if (flag == true) trueParty(i);
		else falseParty.push_back(i);//거짓 파티일 '가능성'있는 파티 저장
	}

}
void trueParty(int Num) {
	int size = party[Num].size();
	for (int i = 0; i < size; i++) {
		heardTrue[party[Num][i]] = 1;
	}
}
int findFalseParty() {

	bool moreParty = true;//새로 확인해야할 거짓파티가 없을때 까지 반복
	while (moreParty) {
		moreParty = false;
		vector<int>newParty;//새로운 false party 담는 용도

		int partyCnt = falseParty.size();
		for (int i = 0; i < partyCnt; i++) {
			bool flag = false;//false party 인지 확인용
			int now = falseParty[i];

			int sizeP = party[now].size();
			for (int j = 0; j < sizeP; j++) {
				if (heardTrue[party[now][j]] == 1) {
					flag = true;//진실 아는 member 발견
					break;
				}
			}

			if (!flag)
				newParty.push_back(now);
			else {//진실 아는 member 발견
				trueParty(now);
				moreParty = true;//while 문 반복하기
			}
		}
		if(moreParty == true) falseParty = newParty;
	}
	
	return falseParty.size();
}