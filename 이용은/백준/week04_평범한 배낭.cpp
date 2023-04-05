#include <iostream>
#include <algorithm>
using namespace std;

int N, K;
int W[100];
int V[100];
int dp[100][100000];//행 : 물건, 열 :  무게
/*
dp 초기값을 반드시 0으로 초기화 해야함
행좌표가 0인 경우는 첫 번째 아이템을 선택할 수 없으므로,
해당 무게에 대한 최대 가치는 항상 0
마찬가지로 열좌표가 0인 경우는 아이템을 선택하지 않는 경우이므로 최대 가치도 0
*/
void input();
int findMaxV(int, int);

int main() {
    input();
    cout << findMaxV(0, K);
    return 0;
}

void input() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);

    cin >> N >> K;
    for (int i = 0; i < N; i++) {
        int w, v;
        cin >> w >> v;
        W[i] = w;
        V[i] = v;
    }
}

//now : 현재 물건, weight : 남은 무게
int findMaxV(int now, int weight) {
    //base
    if (weight < 0) return -21e8;             // weight가 음수인 경우 => 종료(최댓값 될수 없게 만들기)
    if (weight == 0) return 0;                  //무게를 모두 채운 경우=>  시작1
    if (now == N) return 0;                     //모든 물건을 고려한 경우=> 시작2
    if (dp[now][weight] != 0) return dp[now][weight];//중복방지

    //recursive
    int temp1 = findMaxV(now + 1, weight);                                  //현재 물건 선택 안하는 경우
    int temp2 = findMaxV(now + 1, weight - W[now]) + V[now];//현재 물건  배낭에 담는경우

    return dp[now][weight] = max(temp1, temp2);//둘중 최댓값 dp에 저장
}