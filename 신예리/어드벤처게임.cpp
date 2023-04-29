#include <iostream>
#include <cstring>
#include <algorithm>
#include <vector>
using namespace std;

struct info {
    char type;
    int cost;
};

int n;
int fixcost, otherroom;
char room_type;
int flag;
int visited[1001];
vector<int> room_vect[1001];

info room[1001];

// 메모리 : 2716KB 24ms

void dfs(int level, int money)
{ 
    // 레프리콘인 경우면서 소지금이 일정량 미만일 때
    if (room[level].type == 'L' && money < room[level].cost) {
        money = room[level].cost;
    }
    
    // 트롤인 경우
    if (room[level].type == 'T') {
        if (money < room[level].cost) // 소지금이 통행료보다 부족하면 끝내기
            return;
        else {
            money -= room[level].cost; // 충분하면 지불
        }
    }
    // n번 방에 도착했을 때
    if (level == n){
        flag = 1;
        return;
    }
    
    int roomcnt = room_vect[level].size();

    visited[level] = 1;
    for (int i = 0; i < roomcnt; i++){ // 이동 가능한 방으로 dfs
        int to = room_vect[level][i]; 
        if (visited[to] == 0) {
            dfs(to, money);
        }
    }
    visited[level] = 0;
}

int main() {

    ios::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);

    cin >> n; // 미로의 방 수
    while (n != 0) //만약에 방이 0개면 입력을 안받도록
    {
        for (int i = 0; i < 1001; i++) {
            room_vect[i].clear();
        }
        flag = 0;

        for (int i = 1; i <= n; i++){
            cin >> room_type >> fixcost >> otherroom; // 방의 내용물, 정해놓은 금액, 다른 방 문 번호
            room[i].type = room_type;
            room[i].cost = fixcost;
            while (otherroom != 0){ // 0으로 끝날 때까지 입력 받기
                room_vect[i].push_back(otherroom); // 해당 방에서 갈 수 있는 방에 대한 정보를 vect에 담아준다.
                cin >> otherroom;
            }
        }

        dfs(1, 0); 

        if (flag == 1) {
            cout << "Yes\n";
        }
        else {
            cout << "No\n";
        }
        cin >> n;
    }
    return 0;
}