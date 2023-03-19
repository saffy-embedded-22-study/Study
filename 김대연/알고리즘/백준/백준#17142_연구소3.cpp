/*
1. 입력받을때 바이러스 위치 저장. 벽과 바이러스 정보 음수로 바꿔주기. (FloodFill 돌릴때 혼돈 줄 수 있어서)
2. dfs 이용해서 바이러스 조합 구하기.
3. 조합 구한거로 FloodFill 이용해서 다 채우는데 걸리는 시간 구하기.

주의할점!
1. 빈칸이 아예 없을 경우 dfs 할 필요 없음!
2. 바이러스 있던 자리도 queue에 넣어줘야함!

*/

#include <iostream>
#include <algorithm>
#include <vector>
#include <queue>
#include <cstring>
using namespace std;

int N, M;
int Map[60][60];
int diry[4] = {-1, 1, 0, 0};
int dirx[4] = {0, 0, -1, 1};
int EmptyRoom; // 빈 공간 수
int ans = 21e8;

struct node
{
    int y, x;
};
vector<node> v;     // 바이러스 위치 저장
int v_size;         // 바이러스 수
vector<int> Select; // 바이러스 선택

void init()
{
    cin >> N >> M;

    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < N; j++)
        {
            cin >> Map[i][j];
            if (Map[i][j] == 2)
            {
                v.push_back({i, j}); // 바이러스 위치 저장
            }
            if (Map[i][j] != 0)
            {
                Map[i][j] = (-1) * Map[i][j]; // 음수로 바꿔주기
            }
            else
            {
                EmptyRoom++; // 빈 공간 수
            }
        }
    }
    v_size = v.size();
}

int solve()
{
    int CopyMap[60][60];
    memcpy(CopyMap, Map, sizeof(Map));

    queue<node> q;

    int len = Select.size();

    for (int i = 0; i < len; i++)
    {
        q.push(v[Select[i]]);
    }

    int day = 0;
    int cnt = 0; // 바이러스 변이 수

    while (!q.empty())
    {
        int day_len = q.size();
        day++;

        for (int i = 0; i < day_len; i++)
        {
            node now = q.front();
            q.pop();

            for (int dir = 0; dir < 4; dir++)
            {
                int dy = now.y + diry[dir];
                int dx = now.x + dirx[dir];
                if (dy >= N || dy < 0 || dx >= N || dx < 0)
                    continue; // 경계면
                if (CopyMap[dy][dx] == -1)
                    continue; // 벽
                if (CopyMap[dy][dx] > 0)
                    continue; // 방문했던 곳

                q.push({dy, dx});
                if (CopyMap[dy][dx] == -2)
                { // 바이러스 있던 곳 한번 방문했으면 1 처리 해줘야 무한 방문 안함
                    CopyMap[dy][dx] = 1;
                }
                if (CopyMap[dy][dx] == 0)
                {
                    CopyMap[dy][dx] = day;
                    cnt++; // 방문한 곳 수 카운트
                }
                if (cnt == EmptyRoom)
                { // 모든 빈칸을 채웠으면 종료
                    return day;
                }
            }
        }
    }
    return 21e8; // 모든 빈칸 다 못채운 경우
}

void dfs(int level, int start)
{ // 바이러스 선택
    if (level == M)
    {
        ans = min(ans, solve());
        return;
    }

    for (int i = start; i < v_size; i++)
    {
        Select.push_back(i);
        dfs(level + 1, i + 1);
        Select.pop_back();
    }
}

int main()
{
    cin.tie(NULL);
    ios::sync_with_stdio(false);

    init();

    if (EmptyRoom == 0)
    { // 빈 칸이 없을경우
        ans = 0;
    }
    else
    {
        dfs(0, 0);
    }

    if (ans == 21e8)
        cout << -1;
    else
    {
        cout << ans;
    }

    return 0;
}