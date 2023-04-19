#include <iostream>
#include <cmath>
#include <vector>
#include <queue>
#include <cstring>

using namespace std;

int N, Q;
int len;

int MAP[70][70]; // 원본  
int tempMAP[70][70]; // 임시 저장  
int visited[70][70]; // bfs돌릴 때 방문체크

vector<int> vect; // 시전한 단계 저장하는 벡터

int icesum; //정답
int max_ice;

int ydir[4] = { -1,1,0,0 };
int xdir[4] = { 0,0,-1,1 };

struct yx {
    int y;
    int x;
};

void simul();
void rotate(int);
void melt();
int bfs(int, int);


int main(void) {

    cin >> N >> Q;
    len = pow(2, N); // 격자 크기

    for (int i = 0; i < len; i++) {
        for (int j = 0; j < len; j++) {
            cin >> MAP[i][j]; 
        }
    }

    for (int i = 0; i < Q; i++) {
        int step;
        cin >> step;
        vect.push_back(step); // 단계 정보 넣기
    }

    simul();

    cout << icesum << '\n';
    cout << max_ice << '\n';

}

void simul() {

    // 시전한 단계 각각에 대해서 파이어스톰~
    for (int k = 0; k < Q; k++) {
        int size = pow(2, vect[k]);

        rotate(size);
        melt();

    }

    // 남아있는 얼음의 합 구하기  
    for (int i = 0; i < len; i++) {
        for (int j = 0; j < len; j++) {
            if (MAP[i][j] > 0) {
                icesum += MAP[i][j];
            }
        }
    }

    // 가장 큰 덩어리가 차지하는 칸 개수 구하기
    for (int i = 0; i < len; i++) {
        for (int j = 0; j < len; j++) {
            if (visited[i][j] != 1 && MAP[i][j] > 0) {
                int maxi = bfs(i, j); //cnt값 리턴받아서 최대값 갱신
                max_ice = max(max_ice, maxi);
            }
        }
    }

}

void rotate(int size) { // 배열 회전시키는 함수

    // y,x는 몇 번째 격자인지, i,j는 해당 격자내의 인덱스
    for (int y = 0; y < len; y += size) {
        for (int x = 0; x < len; x += size) {

            for (int i = 0; i < size; i++) {
                for (int j = 0; j < size; j++) {
                    tempMAP[j][size - i - 1] = MAP[y + i][x + j]; //  각 격자를 기준으로 회전시켜서 저장  
                }
            }

            for (int i = 0; i < size; i++) {
                for (int j = 0; j < size; j++) {
                    MAP[y + i][x + j] = tempMAP[i][j]; // 저장된 값을 다시 옮기기  
                }
            }
        }
    }
}


void melt() {

    memset(tempMAP, 0, sizeof(tempMAP)); // 녹여야하는 얼음 표시해줄 배열 초기화  

    for (int i = 0; i < len; i++) {
        for (int j = 0; j < len; j++) {

            int cnt = 0;
            for (int di = 0; di < 4; di++) {
                int ny = i + ydir[di];
                int nx = j + xdir[di];

                if (ny < 0 || nx < 0 || ny >= len || nx >= len) continue;
                if (MAP[ny][nx] <= 0) continue;

                cnt++;
            }

            if (cnt < 3) tempMAP[i][j] = -1; // 녹여야하는 얼음 -1로 표시해주기                                
        }
    }

    // 표시해준 얼음 녹이기  
    for (int i = 0; i < len; i++) {
        for (int j = 0; j < len; j++) {
            if (tempMAP[i][j] == -1) {
                MAP[i][j]--;
            }
        }
    }
}

int bfs(int y, int x) {
    // 퍼지면서 큰 덩어리 확인하기
    queue<yx>q;
    q.push({ y, x });
    visited[y][x] = 1;
    int cnt = 1;

    while (!q.empty()) {
        yx now = q.front();
        q.pop();

        for (int di = 0; di < 4; di++) {
            int ny = now.y + ydir[di];
            int nx = now.x + xdir[di];

            if (ny < 0 || nx < 0 || ny >= len || nx >= len) continue;
            if (MAP[ny][nx] <= 0) continue;
            if (visited[ny][nx] == 1) continue;

            visited[ny][nx] = 1;
            cnt++;
            q.push({ ny, nx });
        }
    }

    return cnt;
}