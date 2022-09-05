/* 백준 11280번 2-SAT - 3
*
* Input: 변수의 개수 (1 <= N <= 10,000)과 절의 개수 M (1 <= M <= 100,000)
*		 둘째 줄부터 M개의 줄에는 절이 주어진다.
*		 (1 <= |i|, |j| <= N)으로 이루어져 있으며, i(j)가 양수인 경우 x_i를, 음수인 경우 !x_i를 의미한다.

* Output: 이 CNF가 가능한지 판단하여 가능하면 1, 아니면 0을 출력
*		  이 CNF가 1이 가능하다면 x_1~x_N까지 각각 true인지 false인지 출력한다.
*
*SCC를 이용한다.
*/

#include <iostream>
#include <vector>
#include <stack>
#include <algorithm>
using namespace std;

// 만약 그래프를 인접행렬로 구현할 경우, 메모리 초과가 날 수 있다.	(20,000^2 / 1024^2 = 381)
vector<int> graph[20001];
vector<int> graphT[20001];
int sccLeader[20001];

void DFS1(int _root);			// 원래의 그래프에 적용한 DFS
bool dfsCheck[20001]{ false };	// DFS가 돌았는지 확인하는 배열
stack<int> finishV;	// DFS1을 수행하면서 채울 스택 (DFS가 끝나는 순서대로 쌓는다.)

void DFS2(int _root, int _leader);			// G^T에 적용할 DFS; sccLeader도 매개변수로 전달한다.

vector<pair<int, int>> sccs;	// <sccleader, 정점 인덱스>
int values[10001]{ 0 };		// x_i의 값이 false ->1, true ->2, 미정->0

int main()
{
	// 입력
	int N, M;
	cin >> N >> M;
	for (int m = 0; m < M; m++)
	{
		int i, j;
		cin >> i >> j;

		// CNF가 성립하기 위해서는
		// x_i가 false면 x_j는 true여야 하며
		// x_j가 false면 x_i는 true여야 한다.
		// offset = i + N이다. (N이 10인 경우 x_3은 13, ㄱx_3은 7이다.) (N은 사용하지 않는다.)
		graph[i * -1 + N].push_back(j + N);
		graph[j * -1 + N].push_back(i + N);
	}
	// 초기화
	for (int i = 0; i <= 2 * N; i++)
		sccLeader[i] = -1;

	// SCC를 만든다.
	// 첫번째 DFS를 원래의 Graph에 돌리면서 DFS가 끝나는 순서를 스택에 저장한다.
	for (int i = 0; i <= 2 * N; i++)
	{
		// 해당 정점이 DFS에 의해 방문된 적이 없다면 DFS를 돌린다.
		if (!dfsCheck[i] && i != N)
			DFS1(i);
	}

	// G^T를 만든다.
	for (int i = 0; i <= 2 * N; i++)
	{
		if (i != N)
			for (int j = 0; j < graph[i].size(); j++)
				graphT[graph[i][j]].push_back(i);
	}

	// scc 번호를 별도로 입력한다.
	int sccNum = 0;
	// DFS1에서 Finish된 순서대로 DFS2를 호출한다.
	while (!finishV.empty())
	{
		int curVertex = finishV.top();
		finishV.pop();
		if (sccLeader[curVertex] == -1)
			DFS2(curVertex, sccNum);
		sccNum++;
	}


	// 변수 x_i와 그 역이 같은 SCC에 존재하는지 확인한다.
	// 만약 같은 SCC 안에 존재한다면 이는 성립할 수없다.
	for (int i = 0; i < N; i++)
	{
		if (sccLeader[i] == sccLeader[(i - N) * -1 + N])
		{
			cout << 0 << '\n';
			return 0;
		}
	}
	cout << 1 << '\n';

	// 위상 정렬 순으로 각 정점을 정렬한다.
	for (int i = 0; i <= 2 * N; i++)
	{
		if (i != N)
		{
			sccs.push_back(make_pair(sccLeader[i], i));
		}
	}
	sort(sccs.begin(), sccs.end());
	for (int i = 0; i < sccs.size(); i++)
	{
		int var = sccs[i].second;
		var -= N;
		int varAbs = var;
		if (var < 0) varAbs *= -1;
		if (values[varAbs] == 0)
			values[varAbs] = (var > 0 ? 1 : 2);
	}

	for (int i = 1; i < N + 1; i++)
		cout << values[i] - 1 << ' ';

	return 0;
}

// Finish되는 순서대로 스택에 저장하면서 DFS를 순회한다.
void DFS1(int _root)
{
	dfsCheck[_root] = true;

	if (graph[_root].size() > 0)
	{
		for (int i = 0; i < graph[_root].size(); i++)
			if (!dfsCheck[graph[_root][i]])
				DFS1(graph[_root][i]);
	}

	finishV.push(_root);

	return;
}

void DFS2(int _root, int _leader)
{
	// 이 DFS가 끝나는 것은 현재 돌고 있는 DFS 재귀(SCC 배열의 마지막 SCC 그룹)에 속한다.
	sccLeader[_root] = _leader;

	if (graphT[_root].size() > 0)
	{
		for (int i = 0; i < graphT[_root].size(); i++)
			// sccLeader가 초기값인 0인 경우 아직 방문하지 않은 정점이다.
			if (sccLeader[graphT[_root][i]] == -1)
				DFS2(graphT[_root][i], _leader);
	}
}