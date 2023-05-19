#include <iostream>
#include <vector>
#include<algorithm>
using namespace std;

int N;
vector<int>vect;

int main() {
	
	cin >> N;

	for (int i = 0; i < N; i++) {
		int num;
		cin >> num;
		vect.push_back(num);
	}

	sort(vect.begin(), vect.end());

	int min_sum = 1;

	for (int i = 0; i < N; i++) {
		if (min_sum < vect[i])break;
		min_sum += vect[i];
	}

	cout << min_sum;

	return 0;
}