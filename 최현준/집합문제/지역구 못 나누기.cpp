#include <iostream>
#include <cstring>
#include <vector>
using namespace std;

int T, n;
vector<int>al[9];

int town[9];
int visited[9] = { 0, };

int total, ans, result;


void calc(int now)
{
    int len = al[now].size();
    for (int i = 0; i < len; ++i)
    {
        int target = al[now][i];

        if (visited[target]) continue;

        visited[target] = 1;
        result += town[target];
        int value = abs(2 * result - total);

        ans = min(ans, value);
        calc(target);

        result -= town[target];
    }
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);

    cin >> T;

    for (int tc = 1; tc <= T; ++tc)
    {
        cin >> n;

        int tmp;
        total = 0;
        ans = 21e8;
        result = 0;

        for (int i = 0; i < n; ++i)
        {
            for (int j = 0; j < n; ++j)
            {
                cin >> tmp;

                if (tmp)
                {
                    al[i].push_back(j);
                    al[j].push_back(i);
                }
            }
        }

        for (int i = 0; i < n; ++i)
        {
            cin >> town[i];
            total += town[i];
        }


        for (int i = 0; i < n; ++i)
        {
            visited[i] = 1;
            result += town[i];

            int value = abs(2 * result - total);
            ans = min(ans, value);

            calc(i);

            result -= town[i];
        }

        cout << "#" << tc << " " << ans << '\n';


        for (int i = 0; i < n; ++i)
        {
            al[i].clear();
        }

    }



    return 0;
}