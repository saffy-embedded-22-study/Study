#include <iostream>
#include <algorithm>
#include <cstring>
using namespace std;

int N;
int tree[101];
int ans;
int bigtree;

// 가장 큰 나무와 다른 나무들의 차이가 %2는 1 물뿌리개(홀수)
// /2는 2 물뿌리개를 사용(짝수)
// 홀수와 짝수의 날 중에 더 큰 쪽을 기준으로 날짜 수 갱신
// 짝수인 날을 홀수 이틀로 변경해주면서 짝수인 날이 0보다 작아지면 while문 나오기

int main() {
    
    ios::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);

    int test;
    cin >> test;

    for (int te= 1; te <= test; te++) {

        memset(tree, 0, sizeof(tree));
        ans = 21e8;
        bigtree = -21e8;

        cin >> N;
        for (int i = 0; i < N; i++) {
            cin >> tree[i];
            bigtree = max(bigtree, tree[i]);
        }

        int oddcnt = 0; // 홀수 날짜 수 
        int evencnt = 0; // 짝수 날짜 수 

        for (int i = 0; i < N; i++) {
            int diff = bigtree - tree[i];
            oddcnt += diff % 2;
            evencnt += diff / 2;
        }

        while (evencnt >= 0) {

            //홀수인 날의 수 
            int oddday = oddcnt * 2 - 1;
            //짝수인 날의 수
            int evenday = evencnt * 2;

            int maxday;
             maxday = max(oddday, evenday);

             oddcnt = oddcnt + 2; // 짝수 하루를 홀수 이틀로 바꾸기
             evencnt--; 

             ans = min(ans, maxday); 
            
        }

        cout << "#" << te << " " << ans << '\n';
    }
}