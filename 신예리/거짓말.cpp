#include <iostream>
#include <vector>
using namespace std;

int N, M; // 사람 수, 파티 수
int ans; // 정답
int knowpeo, peonum; // 진실을 알 고 있는 사람 수, 해당 사람의 번호
int partypeo; // 파티에 참석하는 사람 수 
int partypeo_num; // 파티에 참석하는 사람의 번호
int knowpeo_arr[51]; // 진실을 알고 있는 사람은 1로 표시
int lie_possible[51]; // 해당 파티에서 거짓말을 못하면 1 할 수 있으면 0
vector<int>party_info[51]; // 각 파티의 참석한 사람 정보

/* 
메모리 : 2024KB
시간 : 0ms
*/

int main() {

	ios::sync_with_stdio(false);
	cin.tie(NULL); cout.tie(NULL);

	cin >> N >> M; //사람의 수와 파티의 수

	cin >> knowpeo; // 진실을 알고 있는 사람의 수
	for (int i = 0; i < knowpeo; i++) {
		cin >> peonum;
		knowpeo_arr[peonum] = 1;
	}

	for (int i = 0; i < M; i++) {
		cin >> partypeo;
		for (int j = 0; j < partypeo; j++) {
			cin >> partypeo_num;
			party_info[i].push_back(partypeo_num); // 파티번호에 참석 사람 번호 저장
		}
	}

	for (int i = 0; i < M; i++) {
		int len = party_info[i].size();
		for (int j = 0; j < len; j++) {
			int person = party_info[i][j];
			int flag = 0; // 진실을 아는사람이 변경되면 처음 파티부터 다시 확인하기 위해서 flag 설정

			if (knowpeo_arr[person] == 1) {
				lie_possible[i] = 1; // 해당 인덱스 파티에서는 거짓말을 할 수 없음
				for (int k = 0; k < len; k++) { // 만약 진실을 아는 사람이 있는데 그 파티에 진실을 모르는 사람이 있으면 그 사람도 1로 변경
					if (knowpeo_arr[party_info[i][k]] == 0 && j != k) {
						flag = 1;
						knowpeo_arr[party_info[i][k]] = 1;
					}
				}

			}
			if (flag == 1) { //다시 처음 파티부터 가능한지 확인하기
				i = -1;
				break;
			}
		}

	}

	for (int i = 0; i < M; i++) {
		if (lie_possible[i] == 0) ans++;
	}

	cout << ans << '\n';
}