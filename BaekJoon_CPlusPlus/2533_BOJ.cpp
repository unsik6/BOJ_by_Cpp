/* 백준 2533 사회망 서비스(SNS)
*
*Input: 친구 트리의 정점 수 N (2 <= N <= 1'000'000)
*			- 각 정점 번호는 1 ~ N이다.
*		트리의 간선 (u, v) (1 <= u, v <= N)

* Output: 얼리 아답터 정점과 얼리 아답터가 아닌 정점으로 나뉜다.
*		  이때, 얼리 아답터가 아닌 정점은 인접한 모든 정점이 얼리 아답터여야 한다.
		  모든 정점이 얼리 아답터이거나 위 조건을 만족하는 경우에 최소 얼리 아답터 노드의 수를 출력하라.
*/

/*
* 이전에 봤던 DP 문제이다.
* Subtree 단위로 두 가지를 저장하면 된다.
* (1) Node가 얼리 아답터가 아닌 경우	=> 모든 자식 노드들은 얼리 아답터여야 한다.
* (2) Node가 얼리 아답터인 경우			=> 모든 자식 노드들이 얼리 아답터인지 아닌지 상관 없다.
										   모든 '자식 노드를 루트로 하는 서브트리'들이 뱉어내는 최소 얼리 아답터 수를 더해주면 된다.
*/

#include <iostream>
#include <vector>

using namespace std;

#define TE 0	// True Earlyadopter
#define FE 1	// False Earlyadopter

// input
int N;

// graph
// |E| in O(|V|)이므로 Adjaceny list representation이 합리적이다.
// 또한, 메모리 제한이 256MB이고 N <= 1*10^6이므로,
// Adjaceny matrix로 할 경우, 1*10^6MB가 필요해서 불가능하다.
vector<int> graph[1'000'001];

// dpMat[node][case]
int dpMat[1'000'001][2]{ 0 };

// recursive solution
// 트리를 활용하는 문제의 input은 보통 2가지이다.
// (1) {parent, child} 형태로 간선 정보를 받는다.
// (2) {node, node} 형태로 간선 정보를 받는다. 
// 1번의 경우, parent나 child를 저장하는 형식으로 바로 트리를 구성할 수 있다.
// 2번의 경우, graph로 받고 전처리를 통해 앞서 언급한 트리를 구성한다.
// 하지만 이 문제는 부모-자식 관계가 중요한 것이 아니라 '인접'이 중요하다.
// 그러므로 어떤 정점에서 시작하든 똑같다.
void solution(const int _node, const int _parent)
{
	// Base case
	// 문제의 특성상 인접노드가 0개인 케이스는 없긴 하다. (2 <= N)
	// 인접노드가 1개라면 leaf node이다. (1개는 무조건 부모)
	// _parent 검사도 해주는 이유는 노드가 2개일 때,
	// 이 if문에 루트 노드도 걸리는 문제가 있기 때문이다.
	if (graph[_node].size() < 2 && _parent != -1)
	{
		dpMat[_node][TE] = 1;
		// dpMat[_node][FE] = 0;	0으로 초기화라 굳이 필요 없음.
		// 여기서 중요한 점은 Base Case의 solution은 정답이 아니라는 것이다.
		// 만약 트리의 노드가 한개라면 정답은 무조건 1이다. 하지만 위와 같이 저장하면 0이 된다.
		// 그러나 이 문제는 2 <= N이기 때문에 Base case가 정답이 아니더라도 문제 자체는 정답이 도출된다.

		return;
	}

	for (int childIdx = 0; childIdx < graph[_node].size(); childIdx++)
	{
		int childNode = graph[_node][childIdx];
		// 문제에서 트리 형태를 보장하므로, 부모가 아니면 자식이다.
		if (childNode != _parent)
		{
			// 일단 이 자식 놈부터 계산해줘야 한다.
			solution(childNode, _node);

			// (1) 내가 얼리 아답터가 아니다!
			//	   모든 자식이 얼리 아답터인 경우를 더 해주자.
			dpMat[_node][FE] += dpMat[childNode][TE];

			// (2) 내가 얼리 아답터다!
			//		자식의 TE인 경우와 FE인 경우 중에서 작은 것을 더 해주자.
			dpMat[_node][TE] += min(dpMat[childNode][TE], dpMat[childNode][FE]);
		}
	}
	
	dpMat[_node][TE]++;	// 내가 얼리 아답터니까 +1
}

int main()
{
	cin >> N;
	for (int n = 0; n < N - 1; n++)
	{
		int u, v;
		cin >> u >> v;
		graph[u].push_back(v);
		graph[v].push_back(u);
	}

	// 위에서 설명했겠지만, 어디서 시작하든 상관 없다.
	solution(1, -1);

	cout << min(dpMat[1][TE], dpMat[1][FE]);
}