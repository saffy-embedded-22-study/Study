/*
2는 1로 만들 수 있기 때문에 "1" 에 초점.

(1,2)를 한 세트로 보면 최소 세트 수는 총합 /3 에 나머지가 있을 경우 +1

근데 나무 높이 차이 %2 가 1일 경우 무조건 1 물뿌리개가 필요하므로,
%2가 1인 나무의 개수를 세서, 이게 총합/3 + 총합%3 보다 클 경우,
1 개수 * 2 -1 의 일수만큼 필요.

만약 키워야하는 나무 높이가 1 1 1 2 3 일 경우
총합은 8 이므로 필요한 최소 세트 수는 (8/3) + 나머지가 있을경우 +1 = 3세트가 필요하다.
근데 %2==1 인 나무의 수는 1,1,1,3 총 4개이므로 3세트로는 1을 4번 사용하지못하게된다.
따라서 답은 4*2-1 인 7이 된다. (-1하는 이유는 4개세트에서 마지막 2 물뿌리개는 필요 없으므로)
*/

#include <bits/stdc++.h>
using namespace std;

int N;         // 나무 수
int arr[111];  // 나무 높이
int diff[111]; // 최고 높이랑 차이
int ans = 0;   // 정답
int sum = 0;
int bestheight = 0; // 제일 큰 높이
int onecnt = 0;     // %2가 1 개수

void init()
{
    memset(arr, 0, sizeof(arr));
    memset(diff, 0, sizeof(diff));
    cin >> N;
    bestheight = 0;
    for (int i = 0; i < N; ++i)
    {
        cin >> arr[i];
        bestheight = max(bestheight, arr[i]);
    }
    ans = 0;
    sum = 0;
    onecnt = 0;
}

int solve()
{
    for (int i = 0; i < N; ++i)
    {
        diff[i] = bestheight - arr[i];
        sum += diff[i];
        if (diff[i] % 2 == 1)
        {
            onecnt++;
        }
    }

    if (onecnt > sum / 3 + (sum % 3 != 0))
    { // 뒤에 식은 나머지가 있을 경우 1
        return onecnt * 2 - 1;
    }
    else
    {
        return sum / 3 * 2 + sum % 3; // 나머지가 1이면 하루, 2이면 이틀이 필요하므로.
    }
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    int T;
    cin >> T;

    for (int tc = 1; tc <= T; ++tc)
    {
        init();

        ans = solve();

        cout << "#" << tc << ' ' << ans << '\n';
    }

    return 0;
}