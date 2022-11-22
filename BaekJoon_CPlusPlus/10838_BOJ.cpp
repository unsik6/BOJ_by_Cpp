/* 백준 10838 트리
*
* Input: 노드의 수 N ( 1 <= N <= 10^5)
*		 연산의 개수 K ( 1 <= K <= 3*10^5)
*		 연산 r = 1(paint) a, b, c (0 <= a, b <= N-1, 0 <= c <=10^9)
*			  r = 2(move) a, b ( 1<= a <= N-1, 0 <= b <= N-1)
*			  r = 3(count) a, b ( 0 <= a, b <= N -1)
		
		연산:
			paint(a, b, c): a번 노드와 b번 노드를 잇는 최단 경로를 찾은 후, 경로 상에 있는 모든 에지를 색깔 c로 칠한다. 
			move(a, b): a번 노드의 부모 노드를 b번 노드로 바꾼다. 단, b번 노드는 a번 노드를 루트로 하는 부트리(subtree)에 속하지 않는다.
						부모 노드를 바꾸기 전 a번 노드의 부모 노드를 p라 할 때, 새로운 에지 (a,b)는 원래의 에지 (a,p)의 색깔을 갖는다. 
			count(a, b): a번 노드와 b번 노드를 잇는 최단경로를 찾은 후, 그 경로 사이에 있는 에지에 칠해진 서로 다른 색깔의 개수를 출력한다. 
		
		조건:
			초기에 모든 노드는 0의 자식이다. 0은 루트이다.
			paint와 count 연산시 a번 노드와 b번 노드 사이의 최단경로의 길이는 항상 1,000이다.

* Output: 입력에서 주어진 count 연산 각각에 대해 순서대로 결과를 한 줄에 출력한다.
*/

// 최단 경로가 최대 1,000이므로 최단 경로는 LCA를 분기로 한다.
// 단, 고정된 트리가 아니므로 depth 정보를 갱신하는 것이 시간이 더 오래 걸린다.
// 그러므로 루트까지의 경로를 check하는 방향으로 진행한다.

#include <iostream>
#include <utility>
#include <set>

using namespace std;

#define fast_io ios::sync_with_stdio(false); cin.tie(nullptr); cout.tie(nullptr);

// input
int nodeNum, operNum, operId, node1, node2, color;

// tree
int arrParent[100'000]{ 0 };
int arrColor[100'000]{ 0 };

// methods
// 최단 경로 체크할 용도의 배열과 각 연산용 아이디
int checkIdx = 1;
int node1Check[100'000]{ 0 };
int node2Check[100'000]{ 0 };

int findLCA(int _node1, int _node2)
{
	if (_node1 == _node2)
		return _node1;

	int curNode1 = _node1, curNode2 = _node2, lcaIdx = -1;
	node1Check[_node1] = node2Check[_node2] = checkIdx;

	for (int i = 0; i < 1000; i++)
	{
		// 올라가는 중에 루트를 넘어가면 더이상 안 올라감
		if (curNode1 >= 0)
		{
			curNode1 = arrParent[curNode1];
		}
		if (curNode2 >= 0)
		{
			curNode2 = arrParent[curNode2];
		}

		// 다른 경로에서 이미 체크된 것을 만나면 LCA이다.
		if (curNode1 >= 0)
		{
			if (node2Check[curNode1] == checkIdx)
			{
				lcaIdx = curNode1;
				break;
			}
			node1Check[curNode1] = checkIdx;
		}
		if (curNode2 >= 0)
		{
			if (node1Check[curNode2] == checkIdx)
			{
				lcaIdx = curNode2;
				break;
			}
			node2Check[curNode2] = checkIdx;
		}	 
	}

	return lcaIdx;
}

void paint(int _node1, int _node2, int _color)
{
	int lcaIdx = findLCA(_node1, _node2);
	
	// 경로 상에 있는 노드이므로 LCA의 색은 칠하면 안 된다.
	int curNode = _node1;
	while (curNode != lcaIdx)
	{
		arrColor[curNode] = _color;
		curNode = arrParent[curNode];
	}
	curNode = _node2;
	while (curNode != lcaIdx)
	{
		arrColor[curNode] = _color;
		curNode = arrParent[curNode];
	}
}

void move(int _node1, int _node2)
{
	arrParent[_node1] = _node2;
}

int count(int _node1, int _node2)
{
	int lcaIdx = findLCA(_node1, _node2);
	set<int> stColors;

	// 경로 상에 있는 노드이므로 LCA의 색은 보면 안된다.
	int curNode = _node1;
	while (curNode != lcaIdx)
	{
		stColors.insert(arrColor[curNode]);
		curNode = arrParent[curNode];
	}
	curNode = _node2;
	while (curNode != lcaIdx)
	{
		stColors.insert(arrColor[curNode]);
		curNode = arrParent[curNode];
	}

	return stColors.size();
}

int main()
{
	fast_io

	// input & set a tree
	cin >> nodeNum >> operNum;
	arrParent[0] = -1;


	// operate
	for (int o = 0; o < operNum; o++)
	{
		cin >> operId >> node1 >> node2;
		
		switch (operId) {
		case 1:
			cin >> color;
			paint(node1, node2, color);
			break;
		case 2:
			move(node1, node2);
			break;
		case 3:
			cout << count(node1, node2) << '\n';
			break;
		}

		checkIdx++;
	}

	return 0;
}