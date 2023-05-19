#include <iostream>
#include <vector>
using namespace std;

int n, k;
long long d;

struct node
{
	int st;
	int en;
	int interval;
};

vector<node>acorn;

void input()
{
	cin >> n >> k >> d;

	int st, en, interval;

	for (int i = 0; i < k; ++i)
	{
		cin >> st >> en >> interval;
		acorn.push_back({ st, en, interval });
	}
}

void psearch(int left, int right)
{
	int mid;
	long long cnt;
	int ans;

	while (left <= right)
	{
		cnt = 0;
		mid = (left + right) / 2;

		for (int i = 0; i < k; ++i)
		{
			if (mid >= acorn[i].st && mid <= acorn[i].en)
				cnt += (mid - acorn[i].st) / acorn[i].interval + 1;
			else if (mid >= acorn[i].st)
				cnt += (acorn[i].en - acorn[i].st) / acorn[i].interval + 1;
		}

		if (cnt >= d)
		{
			ans = mid;
			right = mid - 1;
		}
		else
			left = mid + 1;
	}
	
	cout << ans;
}


int main()
{
	ios::sync_with_stdio(false);
	cin.tie(NULL); cout.tie(NULL);

	input();
	psearch(0, n);

	return 0;
}