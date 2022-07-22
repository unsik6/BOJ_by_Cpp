// 백준 1931번 동전0

// input: 1 <= N = 회의의 수 <= 100,000
//		  각 회의의 시작시간, 끝 시간. 0 <= s <= f <= 2^31 - 1

// condition: 한 개의 회의실에 가능한 최대의 회의의 수

// activity-selection problem

#include <iostream>
#include <utility>
#include <vector>
#include <algorithm>
using namespace std;

#define PAIR pair<int, int>

bool comparer(PAIR _a, PAIR _b)
{
	// 끝나는 시간이 같은 경우, 시작하는 시간을 오름차순으로 정렬해주어야 한다.
	return (_a.second < _b.second || (_a.second == _b.second && _a.first < _b.first));
}

int main()
{
	int N;
	cin >> N;
	vector<PAIR> dis;
	for (int i = 0; i < N; i++)
	{
		int s, f;
		cin >> s >> f;
		dis.push_back(make_pair(s, f));
	}
	sort(dis.begin(), dis.end(), comparer);

	int m{ 0 }, cnt{ 1 };
	for (int k = 1; k < N; k++)
	{
		if (dis[m].second <= dis[k].first)
		{
			m = k;
			cnt++;
		}
	}

	cout << cnt;
}