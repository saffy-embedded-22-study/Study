#include <bits/stdc++.h>
using namespace std;

int N;           // 사과나무 수
int arr[100010]; // 나무 높이
int sum = 0;     // 높이 합
int evensum = 0; // /2 개수

void init()
{
    cin >> N;
    for (int i = 0; i < N; ++i)
    {
        cin >> arr[i];
        sum += arr[i];
        evensum += (arr[i] / 2);
    }
}

bool solve()
{
    // 총합이 3으로 안나누어떨어지면 불가능.
    if (sum % 3 != 0)
        return false;

    /*  총합을 3으로 나눈것 = 물 뿌리는 횟수
        /2 한것들의 수 = 2 물뿌리개를 뿌릴 수 있는 횟수
        물 뿌리는 횟수가 2 물뿌리개를 이용해야하는 수보다 커지면 불가능.
     */
    if (sum / 3 > evensum)
        return false;

    return true;
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    init();
    bool ans = solve();

    if (ans)
        cout << "YES";
    else
        cout << "NO";

    return 0;
}