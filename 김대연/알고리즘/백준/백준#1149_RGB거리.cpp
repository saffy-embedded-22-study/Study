﻿/*
N 번째 색칠을 할 때, N-1번째의 값을 참고하여 값 갱신하기..

이번에 빨강을 칠하고 싶으면 지난번꺼에에서 파랑, 초록을 칠한 값중 작은값을 가져와서 더해주기.
*/

#include <bits/stdc++.h>
using namespace std;

int N;
int color[1010][3];
int DP[1010][3];

int main()
{
	cin.tie(NULL);
	ios::sync_with_stdio(false);

	cin >> N;

	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			cin >> color[i][j];
		}
	}
	for (int i = 0; i < 3; i++)
	{
		DP[0][i] = color[0][i];
	}

	for (int i = 1; i < N; i++)
	{
		DP[i][0] = min(DP[i - 1][1], DP[i - 1][2]) + color[i][0];
		DP[i][1] = min(DP[i - 1][0], DP[i - 1][2]) + color[i][1];
		DP[i][2] = min(DP[i - 1][0], DP[i - 1][1]) + color[i][2];
	}

	cout << min({DP[N - 1][0], DP[N - 1][1], DP[N - 1][2]});

	return 0;
}