//9704kb 148ms
#include<iostream>
#include <vector>
#include <cstring>
using namespace std;

int n, money, flag;

struct node
{
	char type;
	int cost;
	int to;
};

vector<node>v[1001];
int visited[1001];

void check(int now)
{
	//돈이 같거나 작은 상태로 같은 방을 방문하는 경우 return
	if (visited[now] >= money) return;
	visited[now] = money;

	int len = v[now].size();

	for (int i = 0; i < len; ++i)
	{
		int type = v[now][i].type;
		int cost = v[now][i].cost;
		int to = v[now][i].to;

		//빈 방일 경우 그냥 다른 방 가기
		if (type == 'E')
			check(to);


		//레프리콘일경우 돈 채워주기
		else if (type == 'L')
		{
			int temp = money;
			if (money < cost)
				money = cost;
			check(to);
			money = temp;
		}

		//트롤일경우 통행료 지불하기
		else if (type == 'T')
		{
			int temp = money;
			money -= cost;
			if (money < 0)
			{
				money = temp;
				return;
			}
			check(to);
			money = temp;
		}

		if (now == n)
		{
			flag = 1;
			return;
		}
	}
}

int main()
{
	ios::sync_with_stdio(false);
	cin.tie(NULL); cout.tie(NULL);

	while (1)
	{
		cin >> n;
		//종료조건
		if (n == 0)
			break;

		//초기화
		money = 0;
		flag = 0;

		memset(visited, -1, sizeof(visited));

		for (int i = 1; i <= n; ++i)
			v[i].clear();


		for (int i = 1; i <= n; ++i)
		{
			char ch; int cost; int to;

			cin >> ch >> cost;

			while (1)
			{
				cin >> to;
				if (to == 0)
					break;
				//자기 방 가리킬 때 있어서 생략
				if (to == i)
					continue;

				v[i].push_back({ ch,cost,to });
			}
		}

		check(1);

		if (flag)
			cout << "Yes" << '\n';
		else
			cout << "No" << '\n';
	}

	return 0;
}