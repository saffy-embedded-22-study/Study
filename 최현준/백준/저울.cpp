// 2020KB 0ms

#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;

int n, ans;

vector<int>weight;

void input()
{
	cin >> n;

	ans = 1;
	
	int temp;
	for (int i = 0; i < n; ++i)
	{
		cin >> temp;
		weight.push_back(temp);
	}
}

int main()
{
	input();

	//오름차순 정렬
	sort(weight.begin(), weight.end());

	// 작은 값부터 탐색하면서 i번째까지의 수로 만들 수 있는 무게의 최댓값+1을 ans로 설정한다.
	// 그래서 ans=1로 초기화하였다.
	for (int i = 0; i < n; ++i)
	{
		//만약 i번째의 weight값이 ans(최댓값+1)보다 큰 수 일경우 ans를 만들 수 없으므로 break
		if (weight[i] - ans > 0) break; 
		
		//그렇지 않은 경우 i번째의 weight로 만들 수 있는 ans(최댓값 + 1) 갱신
		else ans += weight[i];
	}

	cout << ans;
	
	return 0;
}