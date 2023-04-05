#include <iostream>
#include <algorithm>
#include <queue>
using namespace std;

int n, m;
int road[1001][1001];

int ydir[4] = { -1,0,1,0 };
int xdir[4] = { 0,-1,0,1 };

struct node
{
    int y;
    int x;
    int cost;
    bool operator < (node next) const {
        if (cost > next.cost) return true;
        return false;
    }
};

priority_queue<node> pq;

int ans[1001][1001] = { 0, };

void bfs(int y, int x)
{
    pq.push({ y, x,road[y][x] });

    for (int i = 0; i < n; ++i)
    {
        for (int j = 0; j < m; ++j)
            ans[i][j] = 21e8;
    }

    while (!pq.empty())
    {
        node now = pq.top(); pq.pop();

        if (now.cost > ans[now.y][now.x]) continue;

        for (int i = 0; i < 4; ++i)
        {
            int ny = now.y + ydir[i];
            int nx = now.x + xdir[i];

            if (ny < 0 || nx < 0 || ny >= n || nx >= m) continue;
            if (road[ny][nx] == -1) continue;

            int ncost = now.cost + road[ny][nx];
            if (ncost >= ans[ny][nx]) continue;

            ans[ny][nx] = ncost;
            pq.push({ ny,nx,ncost });
        }
    }

    if (ans[n - 1][m - 1] == 21e8)
        cout << "-1";
    else
        cout << ans[n - 1][m - 1];
}


int main()
{
    ios::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);

    cin >> n >> m;

    for (int i = 0; i < n; ++i)
    {
        for (int j = 0; j < m; ++j)
            cin >> road[i][j];
    }

    bfs(0, 0);




    return 0;
}