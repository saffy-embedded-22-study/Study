/*
	나무의 최대 높이를 max_height에 저장한 후에
	각 나무와 최대 높이 사이의 거리를 value에 저장한 후 
	odd, even에 필요한 홀수 일 수,짝수 일 수를 저장하였다.
	odd = value%2, even = value/2
	이때 odd는 반드시 필요한 홀수 일 수이다.
	그후 ans라는 함수를 통해서 최소 날짜 수를 구하였다.


*/

#include <iostream>
#include <cstring>
using namespace std;

int T, n;

int tree[101];


// 최소 날짜 수 정하기
int ans(int odd, int even)
{
	if (odd > even) //홀수 > 짝수
		return 2 * odd - 1;

	else if (odd == even) // 같을 때
		return 2 * odd;

	else // 짝수 > 홀수
	{
		while (even - odd > 1) // 짝수가 홀수보다 1일 더 클 때는 홀수로 변환하면 오히려 더 손해
		{
			even -= 1;
			odd += 2;
		}

		if (even >= odd)
			return 2 * even;
		else
			return 2 * odd - 1;
	}

}

int main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(NULL); cout.tie(NULL);

	cin >> T;
	for (int tc = 1; tc <= T; ++tc)
	{
		int max_height = 0;
		int odd = 0;
		int even = 0;

		cin >> n;

		for (int i = 0; i < n; ++i)
		{
			cin >> tree[i];
			max_height = max(max_height, tree[i]);
		}

		for (int i = 0; i < n; ++i)
		{
			int value = max_height - tree[i];
			even += value / 2;
			odd += value % 2;
		}

		cout << "#" << tc << " " << ans(odd, even) << '\n';

	}
	return 0;
}
