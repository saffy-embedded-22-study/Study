// 2020kb 0ms

#include <iostream>
#include <vector>
using namespace std;

int n, m;

int ans;

int parent[51];

vector<int> v[51];

int Find(int now)
{
	if (parent[now] == now)
		return now;

	return parent[now] = Find(parent[now]);
}

void Union(int a, int b)
{
	int pa = Find(a);
	int pb = Find(b);

	if (pa == pb) return;


	// 작은 숫자를 부모로 가지게 조건 설정
	if (pa < pb)
		parent[pb] = pa;
	else
		parent[pa] = pb;

}

int main()
{
	cin >> n >> m;
	ans = m;

	for (int i = 0; i <= n; ++i)
		parent[i] = i;

	int num;
	cin >> num;

	//진실을 아는 사람들의 parent는 모두 0으로 설정
	for (int i = 0; i < num; ++i)
	{
		int a; cin >> a;
		Union(0, a);
	}


	//m개의 파티에서 각 파티에 오는 사람들을 vector에 저장하고 같은 파티에 온 사람들을 union해준다.
	for (int i = 0; i < m; ++i)
	{
		int num; cin >> num;
	
		int flag = 0;
		for (int j = 0; j < num; ++j)
		{
			int a; cin >> a;
			v[i].push_back(a);
			Union(v[i][0], v[i][j]);
		}
	}

	//m개의 파티에서 Find함수를 통해서 0을 부모로 갖는 사람이 한명이라도 있으면 그 파티는 참석 불가
	for (int i = 0; i < m; ++i)
	{
		int len = v[i].size();
		for (int j = 0; j < len; ++j)
		{
			if (!Find(v[i][j]))
			{
				ans--;
				break;
			}
		}
	}

	cout << ans;


	return 0;
}