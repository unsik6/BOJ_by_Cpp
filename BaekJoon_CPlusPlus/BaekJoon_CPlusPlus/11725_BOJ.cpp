// 백준 11725번 트리의 부모 찾기

// input: 노드의 개수 (2<= N <= 100,000)
//		  연결된 정점
// 
// condition: 각 트리의 부모를 출력

// DFS using Matrix : Memory limit
// BFS using Matrix : Memory limit

// edge.size() = O(n) => adjacent list
// edge.size() = O(n^2) => incident Matrix

#include <iostream>
#include <vector>
#include <stack>
using namespace std;

int main()
{
	int N;
	cin >> N;
	vector<int>* adjacent = new vector<int>[N + 1];
	for (int i = 0; i < N - 1; i++)
	{
		int str, dst;
		cin >> str >> dst;
		adjacent[str].push_back(dst);
		adjacent[dst].push_back(str);
	}

	int* parArr = new int[N + 1]{ 0 };
	// DFS
	stack<int> explored;
	explored.push(1);
	while (!explored.empty())
	{
		int cur = explored.top();
		explored.pop();
		for (int e : adjacent[cur])
		{
			if (parArr[e] == 0)
			{
				parArr[e] = cur;
				explored.push(e);
			}
		}
	}

	for (int i = 2; i < N + 1; i++) cout << parArr[i] << '\n';

	delete[] adjacent;
	delete[] parArr;
}