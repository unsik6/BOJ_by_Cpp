/* 백준 2150 Strongly Connected Component
*
*Input: 정점의 수 V, 간선의 수 E (1 <= V <= 10,000 ,1 <= E <= 100,000)
*		정점 번호 A, B ( A -> B, 1 <= A, B <= V )

* Output: 위 규칙 2개를 만족하면서 인원 전체가 앉는 모든 경우의 개수를 구하시오.
*/

// 정점의 개수가 최대10,000개이므로 |V|^2는 100,000,000(약 95 MB)이다.
// E가 경우에 따라 O(|V|^2)이지만 메모리에 여유가 있으므로 Adjacency Matrix를 이용해도 된다.
// 하지만 시간 초과가 발생할 수는 있다. Adjacency Matrix에서는 DFS를 돌리는데 O(|V|^2)이 필요하다.
// 하나의 정점에서 연결된 다른 정점을 찾기 위해 O(|V|)의 시간복잡도가 필요하기 때문이다.
// O(|V|^2) / 100,000,000 = 약 1초이므로 두번의 DFS를 돌려하는 입장에서 시간이 좀 타이트하다.
// 그래서 걍 Adjcency List를 이용하기로 했다. 다만,SCC를 정렬하여 찾을 때는 그냥 O(|V|^2)로 했다.

#include <iostream>
#include <stack>
#include <vector>

using namespace std;

// input
int V, E;

// graph
vector<int> graph[10001];
vector<int> graphT[10001];

// dfs info
bool visited[10001]{ false };

// scc
stack<int> endDFS;
int sccCnt = 0;
int sccLeader[10002]{ 0 };

void firstDFS(int _vIdx)
{
	visited[_vIdx] = true;

	for (int i = 0; i < graph[_vIdx].size(); i++)
	{
		int adjV = graph[_vIdx][i];

		if (!visited[adjV])
		{
			firstDFS(adjV);
		}
	}

	endDFS.push(_vIdx);
}

void reset()
{
	for (int i = 1; i <= V; i++)
		visited[i] = false;
}

void secondDFS(int _vIdx, int _sccL)
{
	visited[_vIdx] = true;
	sccLeader[_vIdx] = _sccL;

	for (int i = 0; i < graphT[_vIdx].size(); i++)
	{
		int adjV = graphT[_vIdx][i];

		if (!visited[adjV])
		{
			secondDFS(adjV, _sccL);
		}
	}
}

int main()
{
	cin >> V >> E;

	for (int e = 0; e < E; e++)
	{
		int a, b;
		cin >> a >> b;
		graph[a].push_back(b);
		graphT[b].push_back(a);
	}

	// first DFS
	for (int i = 1; i <= V; i++)
	{
		if(!visited[i])
			firstDFS(i);
	}

	// reset visited arr
	reset();

	// second DFS
	while (!endDFS.empty())
	{
		int curV = endDFS.top();
		endDFS.pop();
		if (!visited[curV])
		{
			secondDFS(curV, curV);
			sccCnt++;
		}
	}

	// output
	cout << sccCnt << '\n';
	
	for (int i = 1; i <= V; i++)
	{
		if (sccLeader[i] > 0)
		{
			cout << i << ' ';
			for (int j = i + 1; j <= V; j++)
			{
				if (sccLeader[i] == sccLeader[j])
				{
					cout << j << ' ';
					sccLeader[j] = 0;
				}
			}
			
			cout << -1 << '\n';
		}
	}

	return 0;
}