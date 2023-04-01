#include<iostream>
#include<vector>
#include<cstring>
using namespace std;

// 1. 1번은 한 쪽 방향, 2번(서로반대)/3번(직각)은 두 방향, 4번은 세방향, 5번은 네방향
// 2. 상좌하우로 방향벡터 설정해주고 cctv각 상황에 따른 방향 변환
// 3. 한 cctv에 대한 처리 다 한 다음에 다음 cctv로 넘어가서 똑같이 진행

struct yx {
    int y;
    int x;
};

vector<yx>cctv_vect; //cctv

int MAP[9][9]; //MAP설정
int N, M; //세로, 가로

int ydir[4] = { -1,0,1,0 }; //상 좌 하 우
int xdir[4] = { 0,-1,0,1 };
int blind_result = 9999; //정답
int cctv_cnt;

void check(int y, int x, int dir) {

    dir = dir % 4; //0~3을 넘어가는 경우에 0~3의 값으로 변경

    while (1) {
        int ny = y + ydir[dir]; //해당 dir에 대한 방향의 맵 값을 모두 확인하고 변경
        int nx = x + xdir[dir];

        y = ny; // 다음 좌표를 위해서 y,x를 각각 ny, nx값으로 변경 
        x = nx;

        if (ny < 0 || nx < 0 || ny >= N || nx >= M) break; //맵 벗어나면 끝내기
        if (MAP[ny][nx] == 6)break; //벽 만나면 끝내기
        if (MAP[ny][nx] != 0)continue; // cctv가 있을 때는 그 좌표는 넘어서 다음 좌표로
        MAP[ny][nx] = 9;// cctv가 영향을 끼치는 곳 #대신 9로 나타내줌 

    }
}

void simul(int num) {


    if (num == cctv_cnt) { //모든 cctv를 다 살펴봤을 때의 사각지대인 부분의 수 더해주기
        int blind_cnt = 0;
        for (int i = 0; i < N; i++) {
            for (int j = 0; j < M; j++) {
                if (MAP[i][j] == 0) {
                    blind_cnt += 1;
                }
            }
        }
        blind_result = min(blind_result, blind_cnt);
        return;
    }

    yx now = cctv_vect[num];

    int MAP_copy[9][9];

    for (int dir = 0; dir < 4; dir++) {
        memcpy(MAP_copy, MAP, sizeof(MAP));

        if (MAP[now.y][now.x] == 1) {
            check(now.y, now.x, dir);
        }
        else if (MAP[now.y][now.x] == 2) {
            check(now.y, now.x, dir);
            check(now.y, now.x, dir + 2);
        }
        else if (MAP[now.y][now.x] == 3) {
            check(now.y, now.x, dir);
            check(now.y, now.x, dir + 1);
        }
        else if (MAP[now.y][now.x] == 4) {
            check(now.y, now.x, dir);
            check(now.y, now.x, dir + 1);
            check(now.y, now.x, dir + 2);
        }
        else if (MAP[now.y][now.x] == 5) {
            check(now.y, now.x, dir);
            check(now.y, now.x, dir + 1);
            check(now.y, now.x, dir + 2);
            check(now.y, now.x, dir + 3);
        }

        simul(num + 1);

        memcpy(MAP, MAP_copy, sizeof(MAP_copy));
    }


}

int main() {

    ios::sync_with_stdio(false);
    cout.tie(NULL); cin.tie(NULL);

    cin >> N >> M;

    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < M; ++j) {
            cin >> MAP[i][j];
            if (MAP[i][j] >= 1 && MAP[i][j] <= 5) {
                cctv_vect.push_back({ i,j });
            }
        }
    }

    cctv_cnt = cctv_vect.size();

    simul(0);

    cout << blind_result;

    return 0;

}