#include<iostream>
#include<algorithm>
#include<vector>

using namespace std;

int N, M, K;
int nutri_map[11][11]; // 양분에 대한 정보
int add_nutri[11][11]; //각 좌표마다 추가되는 양분의 양
int ans;

vector<int> tree_map[11][11]; // 각 좌표에 나무 정보

int xdir[8] = { -1, -1, -1, 0, 0, 1, 1, 1 };
int ydir[8] = { -1, 0, 1, -1, 1, -1, 0, 1 };

void simul();
void springsummer_simul();
void fall_simul();
void winter_simul();


int main(void) {
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);

    cin >> N >> M >> K; // N크기의 땅/ M개의 줄만큼 나무의 (x,y),나무의 나이/ K년 후
    for (int i = 1; i <= N; i++) {
        for (int j = 1; j <= N; j++) {
            cin >> add_nutri[i][j]; //추가되는 양분의 양
            nutri_map[i][j] = 5; // 처음 양분 5
        }
    }

    // 나무 정보 x,y,age
    for (int i = 0; i < M; i++) {
        int x, y, age;
        cin >> x >> y >> age;
        tree_map[x][y].push_back(age);
    }

    simul();

    cout << ans << '\n';

    return 0;
}

void simul() {
    // K년 만큼 반복해주기
    for (int i = 0; i < K; i++) {
        springsummer_simul();
        fall_simul();
        winter_simul();
    }

    for (int i = 1; i <= N; i++) {
        for (int j = 1; j <= N; j++) {
            ans += tree_map[i][j].size(); // 남아있는 나무 개수 더하기
        }
    }
}

void springsummer_simul() {
    for (int i = 1; i <= N; i++) {
        for (int j = 1; j <= N; j++) {
            if (tree_map[i][j].size() == 0) continue; // 나무가 없으면 패스

            int die_nutri = 0;
            vector<int> new_age; // 새로운 나이들 넣어줄 벡터

            sort(tree_map[i][j].begin(), tree_map[i][j].end()); //나이가 어린 나무부터 양분 먹기

            for (int k = 0; k < tree_map[i][j].size(); k++) {
                int tree_age = tree_map[i][j][k];

                if (nutri_map[i][j] >= tree_age) {
                    nutri_map[i][j] = nutri_map[i][j] - tree_age;
                    new_age.push_back(tree_age + 1);
                }
                else { // 양분이 부족해서 먹을 수 없으면 죽어서 양분으로 변함
                    die_nutri = die_nutri + (tree_age / 2);
                }
            }

            tree_map[i][j].clear(); // 원래있던 것들을 비워주고 새로 값 넣어주기

            for (int k = 0; k < new_age.size(); k++) {
                tree_map[i][j].push_back(new_age[k]); // 저장해뒀던  새로운 나무 나이 좌표에 넣어주기
            }
            nutri_map[i][j] = nutri_map[i][j] + die_nutri; // 죽어서 변한 양분만큼 더해주기
        }
    }
}

void fall_simul() { // 나무 번식
   
    for (int i = 1; i <= N; i++) {
        for (int j = 1; j <= N; j++) {
            if (tree_map[i][j].size() == 0) continue; 

            for (int k = 0; k < tree_map[i][j].size(); k++) {
                int tree_age = tree_map[i][j][k];

                if (tree_age % 5 == 0) { //나이가 5의 배수이면 번식시켜주기
                    for (int di = 0; di < 8; di++) {
                        int nx = i + xdir[di];
                        int ny = j + ydir[di];

                        if (nx < 1 || ny < 1 || nx > N || ny > N)continue;

                        tree_map[nx][ny].push_back(1); // 나이가 1인 나무 추가해주기
                    }
                }
            }
        }
    }
}

void winter_simul() {

    // 각 좌표의 양분을 추가해주기
    for (int i = 1; i <= N; i++) {
        for (int j = 1; j <= N; j++) {
            nutri_map[i][j] = nutri_map[i][j] + add_nutri[i][j];
        }
    }
}