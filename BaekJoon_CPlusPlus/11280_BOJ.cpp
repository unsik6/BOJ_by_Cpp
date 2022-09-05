/* ���� 11280�� 2-SAT - 3
*
* Input: ������ ���� (1 <= N <= 10,000)�� ���� ���� M (1 <= M <= 100,000)
*		 ��° �ٺ��� M���� �ٿ��� ���� �־�����.
*		 (1 <= |i|, |j| <= N)���� �̷���� ������, i(j)�� ����� ��� x_i��, ������ ��� !x_i�� �ǹ��Ѵ�.

* Output: �� CNF�� �������� �Ǵ��Ͽ� �����ϸ� 1, �ƴϸ� 0�� ���
*
*SCC�� �̿��Ѵ�.
*/

#include <iostream>
#include <vector>
#include <stack>
using namespace std;

// ���� �׷����� ������ķ� ������ ���, �޸� �ʰ��� �� �� �ִ�.	(20,000^2 / 1024^2 = 381)
vector<int> graph[20001];
vector<int> graphT[20001];
int sccLeader[20001];

void DFS1(int _root);			// ������ �׷����� ������ DFS
bool dfsCheck[20001]{ false };	// DFS�� ���Ҵ��� Ȯ���ϴ� �迭
stack<int> finishV;	// DFS1�� �����ϸ鼭 ä�� ���� (DFS�� ������ ������� �״´�.)

void DFS2(int _root, int _leader);			// G^T�� ������ DFS; sccLeader�� �Ű������� �����Ѵ�.

int main()
{
	// �Է�
	int N, M;
	cin >> N >> M;
	for (int m = 0; m < M; m++)
	{
		int i, j;
		cin >> i >> j;

		// CNF�� �����ϱ� ���ؼ���
		// x_i�� false�� x_j�� true���� �ϸ�
		// x_j�� false�� x_i�� true���� �Ѵ�.
		// offset = i + N�̴�. (N�� 10�� ��� x_3�� 13, ��x_3�� 7�̴�.) (N�� ������� �ʴ´�.)
		graph[i * -1 + N].push_back(j + N);
		graph[j * -1 + N].push_back(i + N);
	}
	// �ʱ�ȭ
	for (int i = 0; i <= 2 * N; i++)
		sccLeader[i] = -1;

	// SCC�� �����.
	// ù��° DFS�� ������ Graph�� �����鼭 DFS�� ������ ������ ���ÿ� �����Ѵ�.
	for (int i = 0; i <= 2 * N; i++)
	{
		// �ش� ������ DFS�� ���� �湮�� ���� ���ٸ� DFS�� ������.
		if (!dfsCheck[i] && i != N)
			DFS1(i);
	}

	// G^T�� �����.
	for (int i = 0; i <= 2 * N; i++)
	{
		if (i != N)
			for (int j = 0; j < graph[i].size(); j++)
				graphT[graph[i][j]].push_back(i);
	}

	// DFS1���� Finish�� ������� DFS2�� ȣ���Ѵ�.
	while (!finishV.empty())
	{
		int curVertex = finishV.top();
		finishV.pop();
		if (sccLeader[curVertex] == -1)
			DFS2(curVertex, curVertex);
	}

	// ���� x_i�� �� ���� ���� SCC�� �����ϴ��� Ȯ���Ѵ�.
	for (int i = 0; i < N; i++)
	{
		if (sccLeader[i] == sccLeader[(i - N) * -1 + N])
		{
			cout << 0;
			return 0;
		}
	}

	cout << 1;
	return 0;
}

// Finish�Ǵ� ������� ���ÿ� �����ϸ鼭 DFS�� ��ȸ�Ѵ�.
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
	// �� DFS�� ������ ���� ���� ���� �ִ� DFS ���(SCC �迭�� ������ SCC �׷�)�� ���Ѵ�.
	sccLeader[_root] = _leader;

	if (graphT[_root].size() > 0)
	{
		for (int i = 0; i < graphT[_root].size(); i++)
			// sccLeader�� �ʱⰪ�� 0�� ��� ���� �湮���� ���� �����̴�.
			if(sccLeader[graphT[_root][i]] == -1)
				DFS2(graphT[_root][i], _leader);
	}
}