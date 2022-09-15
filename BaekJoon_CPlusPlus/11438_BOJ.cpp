/* 백준 11437번 LCA
*
* Input: 노드의 개수 N ( 2<= N <= 100,000 )
*		 1번이 루트인 트리 입력 -> 트리 연결된 두 노드 입력
*		 두 노드의 쌍(쿼리의 수) M ( 1 <= M <= 100,000 )
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
#include <math.h>
using namespace std;

#define INT_VEC vector<int>

// Information of tree
int depths[100001]{ 0 };
int parents[100001][17];	// parents[[i][k] = i번 노드의 2^k번째 부모
							// n이 100,000이므로 2^16번째 부모까지만 넣을 수 있다.
int max_depth;

INT_VEC graph[100001];	// 트리를 구성하기 위한 그래프

// input
int n, m;

// BFS로 트리 정보 구성
void set_tree(int _node, int _par, int _d)
{
	depths[_node] = _d;
	parents[_node][0] = _par;

	// 조상들 구하기
	// child의 2^k번째 조상은
	// child의 2^(k-1)번째 조상의 2^(k-1)번째 조상
	for (int i = 1; i <= max_depth; i++)
		parents[_node][i] = parents[parents[_node][i - 1]][i - 1];

	for (int i = 0; i < graph[_node].size(); i++)
	{
		int child = graph[_node][i];
		if (child == _par) continue;	// 트리여서 이 경우가 아니면 방문했던 노드를 방문할 일이 없다.
		set_tree(child, _node, _d + 1);
	}
}

int main()
{
	ios::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(NULL);

	cin >> n;
	for (int i = 0; i < n - 1; i++)
	{
		int v, w;
		cin >> v >> w;

		graph[v].push_back(w);
		graph[w].push_back(v);
	}

	max_depth = (int)floor(log2(100000));

	// BFS로 트리 정보 구성
	set_tree(1, 0, 1);

	// 쿼리 수행
	cin >> m;
	int v, w;
	for (int t = 0; t < m; t++)
	{
		cin >> v >> w;
		
		if (v == 1 || w == 1)
		{
			cout << 1 << '\n';
			continue;
		}

		// w가 더 큰 깊이를 갖도록 조정
		if (depths[v] > depths[w])
			v ^= w ^= v ^= w;

		// 두 노드의 depth 맞추기
		// 이진 탐색으로 진행한다. 가장 멀리 있는 조상부터 확인한다.
		if (depths[v] != depths[w])
		{
			for (int i = max_depth; i >= 0; i--)
			{
				if (depths[parents[w][i]] >= depths[v])
					w = parents[w][i];

				// w = parents[w][k]로 갱신한 이후
			// parents[w][k]의 2^k번째 조상은 볼 필요가 없다는 것이다.
			// parents[w][k]의 2^k번째 조상은 parents[w][k+1]과 같기 때문이다.
			}
		}

		// lca 찾기
		if (v != w)
		{
			for (int i = max_depth; i >= 0; i--)
			{
				if (parents[v][i] != parents[w][i])
				{
					v = parents[v][i];
					w = parents[w][i];
				}
				// v와 w의 조상들 중 LCA보다 위에 있는 조상들도 모두 공통 조상이다.
				// 그러므로 depth 맞추기와 동일하게 이진탐색으로 올라간다.
			}
			// 최종적으로 lca 바로 아래 노드가 저장된다.
			v = parents[v][0];
		}

		cout << v << '\n';
	}

	return 0;
}