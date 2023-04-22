/*
Union-Find 이용해서 같은 파티 온사람들 끼리 연결하기!
진실을 알고 있는 사람의 부모를 -1로 세팅하기.
*/

#include<bits/stdc++.h>
using namespace std;

int N, M;
int parent[55];
vector<int> party[55];

int Find(int now);
void Union(int a, int b);


int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> N >> M;

    for (int i = 1; i <= N; ++i) {
        parent[i] = i;
    }

    int num;
    cin >> num;

    for (int i = 0; i < num; ++i) { // 진실 아는 사람들의 부모를 -1로 세팅
        int temp;
        cin >> temp;
        parent[temp] = -1;
    }

    for (int i = 0; i < M; ++i) {   // 파티 정보 입력
        cin >> num;

        for (int j = 0; j < num; ++j) {
            int temp;
            cin >> temp;
            party[i].push_back(temp);
        }
    }

    for (int i = 0; i < M; ++i) {
        
        int len = party[i].size();

        for (int j = 0; j < len; ++j) { // 같은 파티 온사람들끼리 -1 세팅
            for (int k = j + 1; k < len; ++k) {
                Union(party[i][j], party[i][k]);
            }
        }
    }

    int ans = 0;

    for (int i = 0; i < M; ++i) {   // 파티 온 사람들 부모를 확인. -1이 있으면 못감.
        int len = party[i].size();
        bool flag = true;

        for (int j = 0; j < len; ++j) {
            if (Find(party[i][j]) == -1) {
                flag = false;
                break;
            }
        }
        if (flag) ans++;
    }
    
    cout << ans;

    return 0;
}

int Find(int now) {
    if (parent[now] == -1)
        return -1;
    if (now == parent[now])
        return now;
    return parent[now] = Find(parent[now]);
}

void Union(int a, int b) {
    int pa = Find(a);
    int pb = Find(b);

    if (pa == pb) return;

    if (pa == -1) {
        parent[pb] = pa;
    }
    else if (pb == -1) {
        parent[pa] = pb;
    }
    else {
        parent[pb] = pa;
    }
}