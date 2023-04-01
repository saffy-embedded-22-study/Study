/*
parametric search를 이용하여 해결하였음.

st = 테이블의 최대값
en = 테이블 사람들의 합계

mid값을 설정하고 그 값을 넘지 않는 선에서 팀원을 나누고 그 때의 팀의 개수를 cnt라고 할 때

cnt<=T 일 때(팀이 적거나 적절하게 만들어지는 경우) mid값이 정답보다 크거나 같은 경우 => right = mid -1

cnt > T 일 때 (팀이 많이 만들어지는 경우) mid값이 정답보다 작은 경우 => left = mid+1

st부터 en사이의 값 중 cnt의 값이 변하는 경계면에서의 값(mid)가 우리가 원하는 정답
*/

#include <iostream>
#include <cstring>
using namespace std;

int n, t;

int table[1001];

// 모든 케이스에 대해 팀의 개수를 센다
// 단, cnt <= t를 만족하는 경우가 한 가지라도 있으면 true를 반환
// false인 경우는 모든 케이스에 대해서 cnt > T인 경우
bool condition(int now)
{
	for (int i = 0; i < n; ++i)
	{
		int tmp = 0;
		int cnt = 0;
		for (int j = i; j < i + n; ++j)
		{
			tmp += table[j];

			if (tmp > now)
			{
				tmp = table[j];
				cnt++;
			}

			if (cnt >= t) break;
		}
		cnt++;

		if (cnt <= t)
			return true;
	}
	return false;
}


int psearch(int left, int right)
{
	int mid;
	int ans;
	while (left <= right)
	{
		mid = (left + right) / 2;

		if (condition(mid))
		{
			// condition이 true일 때의 mid값이 정답이므로 mid의 값을 따로 ans에 저장해둔다.
			ans = mid;
			right = mid - 1;
		}

		else
			left = mid + 1;
	}
	return ans;
}

int main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(NULL); cout.tie(NULL);

	cin >> n >> t;
	
	int st = -21e8;
	int en = 0;

	for (int i = 0; i < n; ++i)
	{
		cin >> table[i];
		table[i + n] = table[i];

		st = max(st, table[i]);
		en += table[i];
	}
	cout << psearch(st, en);

	return 0;
}