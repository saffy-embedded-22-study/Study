/*
Parametric Search 이용!
팀을 나눌 수 있는 최대값을 기준으로 PS 진행!
팀 개수가 T개 이하면 true -> 값을 줄여가면서 PS 진행 -> 가능한 가장 작은값 찾기


*/

#include <bits/stdc++.h>
using namespace std;

int N, T;
int arr[500];

bool condition(int cut)
{
    int now = 0;
    int cnt = 0;

    for (int i = 0; i < N; ++i)
    {
        if (arr[i] > cut)
            return false; // cut보다 큰 값이 있으면 false
    }

    for (int i = 0; i < N; i++)
    {

        now = 0;
        cnt = 1;
        for (int j = 0; j < N; j++)
        {
            int cur = i + j;
            if (cur >= N)
                cur -= N;

            if (now + arr[cur] > cut)
            { // 합이 cut을 넘게 되면 다음 그룹으로
                cnt++;
                now = arr[cur];
            }
            else
            {
                now += arr[cur];
            }
        }
        if (cnt <= T)
        {
            return true;
        }
    }
    return false;
}

int ps()
{
    int left = 0;
    int right = N * 100000;

    int cnt = 0;
    int ans = 0;
    while (left <= right)
    {
        int mid = (left + right) / 2;

        if (condition(mid) == true)
        {
            ans = mid;
            right = mid - 1;
        }
        else
        {
            left = mid + 1;
        }
    }
    return ans;
}

int main()
{
    cin >> N >> T;

    for (int i = 0; i < N; i++)
    {
        cin >> arr[i];
    }
    int ans = ps();
    cout << ans;

    return 0;
}