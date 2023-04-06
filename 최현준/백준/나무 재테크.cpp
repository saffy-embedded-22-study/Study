#include <iostream>
#include <queue>
#include <algorithm>
using namespace std;

int n, m, k, ans;

int field[11][11]; // 현재 양분을 나타내는 배열
int nutrient[11][11] = { 0, }; // 겨울에 추가할 양분을 나타내는 배열

struct node
{
	int y;
	int x;
	int age;
	bool operator < (node next) const
	{
		if (age < next.age) return true;
		return false;
	}
};

vector<node>tree; // 나무
vector<node>alive; // 살아있는 나무
vector<node>dead; // 죽은 나무

int ydir[8] = { -1,-1,0,1,1,1,0,-1 };
int xdir[8] = { 0,1,1,1,0,-1,-1,-1 };

void input()
{
	cin >> n >> m >> k;
	tree.reserve(n*n);
	alive.reserve(n*n);
	dead.reserve(n*n);

	for (int i = 1; i <= n; ++i)
	{
		for (int j = 1; j <= n; ++j)
			cin >> nutrient[i][j];
	}

	for (int i = 0; i < m; ++i)
	{
		int y, x, age;
		cin >> y >> x >> age;

		tree.push_back({ y,x,age });
	}

	for (int i = 1; i <= n; ++i)
	{
		for (int j = 1; j <= n; ++j)
			field[i][j] = 5;
	}

}

void season()
{
	//spring
	//age 순으로 정렬
	sort(tree.begin(), tree.end());

	int tree_len = tree.size();

	for (int i = 0; i < tree_len; ++i)
	{
		node now = tree[i];

		int y = now.y;
		int x = now.x;
		int age = now.age;

		if (age > field[y][x])
		{
			dead.push_back({ y,x,age });
			continue;
		}

		field[y][x] -= age;

		alive.push_back({ y,x,age + 1 });
	}

	int alive_len = alive.size();
	int dead_len = dead.size();

	tree.clear();

	for (int i = 0; i < alive_len; ++i)
	{
		node now = alive[i];
		tree.push_back({ now.y, now.x, now.age });
	}

	//summer
	for (int i = 0; i < dead_len; ++i)
	{
		node now = dead[i];

		field[now.y][now.x] += now.age / 2;
	}


	//fall
	for (int i = 0; i < alive_len; ++i)
	{
		node now = alive[i];

		if (now.age % 5 == 0)
		{
			for (int j = 0; j < 8; ++j)
			{
				int ny = now.y + ydir[j];
				int nx = now.x + xdir[j];

				if (ny <= 0 || nx <= 0 || ny > n || nx > n) continue;

				tree.push_back({ ny,nx,1 });
			}
		}
	}

	//winter
	for (int i = 1; i <= n; ++i)
	{
		for (int j = 1; j <= n; ++j)
			field[i][j] += nutrient[i][j];
	}

	alive.clear();
	dead.clear();
}


int main()
{
	ios::sync_with_stdio;
	cin.tie(NULL); cout.tie(NULL);

	input();
	while(k--)
		season();

	cout << tree.size();


	return 0;
}