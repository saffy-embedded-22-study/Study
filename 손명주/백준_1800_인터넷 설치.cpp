#include <iostream>
#include <vector>
#include <queue>
using namespace std;

int N, P, K; //2448kb 4ms
struct Line {
    int to; //1부터 N;
    int cost;
};
struct Link {
    int me;
    int overx;
};
vector<Line> al[1001];
int Over[1001];
struct cmp {
    bool operator ()(Link left, Link right) {
        if (left.overx > right.overx) return true;
        if (left.overx < right.overx) return false;
        return false;
    }
};

bool Possible(int x) {
    for (int i = 1; i <= N; i++) Over[i] = 2000;
    priority_queue<Link, vector<Link>, cmp> pq;
    pq.push({ 1,0 });
    Over[1] = 0;

    while (!pq.empty()) {
        Link now = pq.top();
        pq.pop();
        if (now.overx > K) return false;
        if (now.me == N) return true;

        int n = al[now.me].size();
        for (int i = 0; i < n; i++) {
            Line next = al[now.me][i];

            int overx = now.overx + (next.cost > x);
            if (Over[next.to] <= overx) continue;
            Over[next.to] = overx;

            pq.push({ next.to, overx });
        }
    }
    return false;
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);

    cin >> N >> P >> K;
    for (int i = 0; i < P; i++) {
        int a, b, c;
        cin >> a >> b >> c;
        al[a].push_back({ b,c });
        al[b].push_back({ a,c });
    }
    int left = -1;
    int cannot = 1000001;
    int right = cannot;
    

    while (left + 1 < right) {
        int mid = (left + right) / 2;
        if (Possible(mid)) right = mid;
        else left = mid;
    }
    if (right == cannot) cout << -1;
    else cout << right;

    return 0;
}