// 백준 1202번 보석 도둑

// input: 보석의 개수 N, 가방의 개수 K (1 <= N, K <= 300,000)
//		  각 보석의 무게 Mi, 가치 Vi (0 <= Mi, Vi <= 1,000,000)
//		  가방에 담을 수 있는 최대 무게 Ci (1 <= Ci <= 100,000,000)

// condition: 각각의 가방에는 최대 한 개의 보석만 넣을 수 있다.

// output: 훔친 보석들의 가치의 총합이 최대가 될 때의 가치의 총합

// 1. 가방의 무게를 오름차순으로 정렬한다.
// 2. 무게를 중심으로 오름차순으로 정렬한다.
// 3. 각 가방에 대하여 2번에서 정렬된 것 중 넣을 수 있는 가장 앞선 보석을 넣는다.

// 이때 3에서 단순히 다중반복문으로 매 가방에 대하여 남아있는 모든 보석을 비교하면 시간초과가 발생한다.
// 우선순위큐를 사용한다.
// 각 가방 무게에 대하여 넣을 수 있는 보석들의 가치를 우선순위큐에 넣는다.
// 그리고 가방 1개를 소모하여 우선순위큐에서 pop을 한다.
// 위 방법은 다음과 같은 전제를 만족한다.
// 가치가 가장 높은 보석 중 가져갈 수 있는 보석을 먼저 소모한다.
// 어차피 가방이 오름차순이므로 우선순위큐에 있는 보석들은 가져갈 수 있는 보석들이다.

#include <iostream>
#include <utility>
#include <vector>
#include <queue>
#include <algorithm>
using namespace std;

#define jewel pair<int, int>



bool compareJewel(jewel _a, jewel _b)
{
	if (_a.first != _b.first)
	{
		return (_a.first < _b.first);
	}
	else
	{
		return (_a.second > _b.second);
	}
}

long long maxValue(vector<jewel>& _jewels, int _n, vector<int>& _bags, int _k)
{
	
	long long totalValue = 0;
	priority_queue<int> pq;
	int jewelIdx = 0;
	for (int k = 0; k < _k; k++)
	{
		while (jewelIdx < _n && _jewels[jewelIdx].first <= _bags[k])
		{
			pq.push(_jewels[jewelIdx].second);
			jewelIdx++;
		}
		if (!pq.empty())
		{
			totalValue += (long long)pq.top();
			pq.pop();
		}
	}

	return totalValue;
}

int main()
{
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	int N, K;
	cin >> N >> K;
	vector<jewel> jewels;
	for (int i = 0; i < N; i++)
	{
		int M, V;
		cin >> M >> V;
		jewels.push_back(make_pair(M, V));
	}
	vector<int> bags;
	for (int k = 0; k < K; k++)
	{
		int bag;
		cin >> bag;
		bags.push_back(bag);
	}
	
	sort(jewels.begin(), jewels.end(), compareJewel);
	sort(bags.begin(), bags.end());

	cout << maxValue(jewels, N, bags, K);
	return 0;
}