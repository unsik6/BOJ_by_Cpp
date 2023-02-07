/* 백준 2516 원숭이
*
*Input: 원숭이 수 N (3 <= N <= 100,000)
*		N개의 줄에 앙숙관계 원숭이 수 M, 앙숙관계 원숭이 번호 M개 (0 <= M <= N-1)

* Output: 2케이지에 원숭이들을 넣을거임.
*		  1) 각 원숭이에 대하여 같은 케이지에 앙숙관계인 원숭이는 최대 1마리여야 한다.
*		  2) 모든 원숭이를 한 케이지에 넣으면 안 된다.
*/

#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>

using namespace std;

// input
int N;

// graph
// Adjacency Matrix 사용 M in O(N^2)임
// 근데 10만*10만하면 bit 단위로 저장한다고 해도 1250MB임 ㄷㄷ
// 못 나누는 경우는 없다고 했으니까 그렇게까지 간선이 많지 않을테니 Adjacency List로 해보자.
// 실제로 정점을 두개의 집합으로 나눈다고 했을 때, 그 크기를 각각 a, b라고 해보자.
// 한 집합 안에서 존재할 수 있는 간선의 최대 개수는 floor(a/2) 또는 floor(b/2)이다.
// 그리고 각 집합 사이에 존재할 수 있는 간선의 개수는 ab이다.
// b = N - a이므로 a(N-a)가 된다.
// 그러므로 총 간선의 수는 a(N-a) + N/2라고 할 수 있다.
// a가 커질수록 N-a도 커지므로 최악의 경우에는 O(N^2)이지만 N^2/4 + N/2이다.

vector<int> graph[100001];
int monkeys[100001];
bool cageOfMonkeys[100001]{ false };	// 0 또는 1

bool comp(int _a, int _b)
{
	if (graph[_a].size() != graph[_b].size())
		return graph[_a].size() > graph[_b].size();
	return _a < _b;
}

void input()
{
	cin >> N;
	for (int monIdx = 1; monIdx <= N; monIdx++)
	{
		int M, devil;
		cin >> M;
		for (int m = 0; m < M; m++)
		{
			cin >> devil;
			graph[monIdx].push_back(devil);
		}
	}
}

void solution()
{
	bool flag = true;
	while (flag)
	{
		flag = false;
		for (int i = 1; i <= N; i++)
		{
			int cnt = 0;
			for (int j = 0; j < graph[i].size(); j++)
				cnt += (cageOfMonkeys[i] == cageOfMonkeys[graph[i][j]]);
			if (cnt > 1)
			{
				cageOfMonkeys[i] = !cageOfMonkeys[i];
				flag = true;
			}
		}
	}
}

void output()
{
	vector<int> a, b;
	for (int i = 1; i <= N; i++)
		cageOfMonkeys[i] ? a.push_back(i) : b.push_back(i);

	// a가 비어있을 경우 (true 라벨 케이지)
	if (a.empty())
	{
		a.push_back(b.back());
		b.pop_back();
	}

	cout << a.size() << ' ';
	for (int i = 0; i < a.size(); i++)
		cout << a[i] << ' ';
	cout << '\n';

	cout << b.size() << ' ';
	for (int i = 0; i < b.size(); i++)
		cout << b[i] << ' ';
}


int main()
{
	input();
	solution();
	output();
	return 0;
}