#include <iostream>
#include <cstring>
#include <vector>
#include <queue>
using namespace std;

int n, m, k;

struct fire {
    int y;
    int x;
    int mass;
    int speed;
    int dir;
};

fire field[51][51];

int ydir[8] = { -1,-1,0,1,1,1,0,-1 };
int xdir[8] = { 0,1,1,1,0,-1,-1,-1 };
int visited[51][51] = { 0, };

queue<fire>q;
vector<fire>v[51][51];

void spell()
{
    while (k--)
    {
        while (!q.empty())
        {
            fire now = q.front(); q.pop();
            int y = now.y;
            int x = now.x;
            int mass = now.mass;
            int speed = now.speed;
            int dir = now.dir;

            int ny; int nx;

            for (int s = 0; s < speed; ++s)
            {
                ny = (y + ydir[dir] + n) % n;
                nx = (x + xdir[dir] + n) % n;
                y = ny;
                x = nx;
            }

            visited[ny][nx] ++;
            v[ny][nx].push_back({ ny,nx,mass,speed,dir });
            //cout << ny << " " << nx << " " << visited[ny][nx] << '\n';
        }

        for (int i = 0; i < n; ++i)
        {
            for (int j = 0; j < n; ++j)
            {
                if (visited[i][j] >= 2)
                {
                    int len = v[i][j].size();

                    int main_dir = v[i][j][0].dir % 2; // 첫번째 방향

                    int flag = 0;

                    int mass_sum = 0;
                    int speed_sum = 0;

                    for (int k = 0; k < len; ++k)
                    {
                        fire tmp = v[i][j][k];
                        mass_sum += tmp.mass;
                        speed_sum += tmp.speed;
                        int tog = tmp.dir % 2;
                        if (main_dir != tog) flag = 1; // 모두 홀수거나 짝수가 아닌 경우
                    }

                    if (mass_sum / 5 != 0)
                    {
                        int nmass = mass_sum / 5;
                        int nspeed = speed_sum / len;
                        //cout << nmass << " " << nspeed << " " << flag << '\n';

                        if (flag)
                        {
                            for (int d = 1; d < 8; d += 2)
                                q.push({ i,j,nmass,nspeed, d });
                        }
                        else
                        {
                            for (int d = 0; d < 8; d += 2)
                                q.push({ i,j,nmass,nspeed, d });
                        }
                    }

                    v[i][j].clear();
                }
                if (visited[i][j] == 1)
                {
                    fire tmp = v[i][j][0];
                    //cout << "done" << '\n';
                    q.push({ i,j,tmp.mass,tmp.speed,tmp.dir });
                }
                visited[i][j] = 0;
            }
        }
    }
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);

    cin >> n >> m >> k;

    for (int i = 0; i < m; ++i)
    {
        int r, c, m, s, d;
        cin >> r >> c >> m >> s >> d;
        q.push({ r - 1,c - 1,m,s,d });
    }

    spell();

    int ans = 0;

    while (!q.empty())
    {
        fire now = q.front(); q.pop();
        ans += now.mass;
    }

    cout << ans;
    return 0;
}