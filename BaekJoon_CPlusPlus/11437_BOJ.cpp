/* 백준 11437번 LCA
*
* Input: 노드의 개수 N ( 2<= N <= 50,000 )
*		 1번이 루트인 트리 입력 -> 트리 연결된 두 노드 입력
*		 두 노드의 쌍(쿼리의 수) M ( 1 <= M <= 10,000 )
* 
*		 * 각 트리의 정점은 1~N으로 인덱싱되어 있음

* Output: 쿼리 쌍에 대한 LCA 출력
* 
* 제곧내
*/

#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
using namespace std;

#define INT_VEC vector<int>


// Information of tree
int depths[50001]{ 0 };
int parent[50001]{ 0 };

INT_VEC graph[50001];

// input
int n, m;

int main()
{
	cin >> n;
	
	// 노드 간의 관계 입력 받기
	// BFS 이용
	for (int i = 0; i < n - 1; i++)
	{
		int v, w;
		cin >> v >> w;
		graph[v].push_back(w);
		graph[w].push_back(v);
	}

	queue<int> bfsQ;
	bfsQ.push(1);
	while (!bfsQ.empty())
	{
		int cur = bfsQ.front();
		bfsQ.pop();

		for (int i = 0; i < graph[cur].size(); i++)
		{
			// 이미 방문한 노드(노드 번호 1 또는 depth가 존재함)는 방문 안 함
			if (graph[cur][i] != 1 && parent[graph[cur][i]] == 0)
			{
				bfsQ.push(graph[cur][i]);
				depths[graph[cur][i]] = depths[cur] + 1;
				parent[graph[cur][i]] = cur;
			}
		}
	}
	
	// 쿼리 수행
	cin >> m;
	for (int i = 0; i < m; i++)
	{
		int v, w;
		cin >> v >> w;
		// v를 depth가 더 작은 노드로
		if (depths[v] > depths[w]) v ^= w ^= v ^= w;
		
		// depths 맞추기
		while(depths[w] != depths[v])
			w = parent[w];

		// 거슬러 올라가기
		// 만약 v와 w의 부모가 같을 때까지 올라갈 경우
		// 거슬러 올라가기가 끝나고 parent[v]를 lca라고 하면 안 된다.
		//  v 또는 w 노드 자체가 공통 조상이 되는 case인 경우를 고려해줘야 한다.
		while (w !=v)
		{
			w = parent[w];
			v = parent[v];
		}

		cout << v << '\n';
	}

	return 0;
}
